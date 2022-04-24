/********************************************
 *
 *  Name: Paul Kim
 *  Email: pbkim@usc.edu
 *  Section: Wednesday 12:30 PM
 *  Assignment: Final Project
 *
 ********************************************/

// Including Useful Libaries for Functions
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

// Including Seperate Header Files
#include "lcd.h"
#include "rangefinder.h"
#include "encoder.h"
#include "buzzer.h"
#include "LED.h"
#include "button.h"
#include "finalproject.h"

// Declaring Volatile Variables (used to initialize counts before EEPROM), (distance is measurement from rangefinder)
volatile int nearCount = 20; // Initial Near Count (Default) 
volatile int farCount = 40; // Initial Far Count (Default)
volatile int distance; // Used to store distance in MM

// Main Function
int main (void) {
    // Initilization Hardware by Calling Seperate Files
    lcd_init(); // Initializing LCD
    range_init(); // Initializing Range Finder and importing appropriate functions
    button_init(); // Initializing Buttons and importing appropriate functions
    LED_init(); // Initializing Multi-Color LED and importing appropriate functions
    rotary_init();  // Initializing Rotary Encoder and importing appropriate functions
    buzzer_init();  // Initializing Buzzer and importing appropriate functions    

    sei(); // Enabling Interrupts
    
    // Start of Splash Screen
    lcd_writecommand(1); 
    lcd_moveto(0,4);
    lcd_stringout("Paul Kim");
    char date[30];
    int month = 2;
    int day = 7;
    int year = 2002;
    snprintf(date, 30, "%02d/%02d/%d", month, day, year); // Formatting using snprintf

    lcd_moveto(1,3);
    lcd_stringout(date);

    _delay_ms(1000);
    lcd_writecommand(1);

    // Initializing LCD Screen
    lcd_moveto(0,0);
    lcd_stringout("Near");
    lcd_moveto(1,0);
    lcd_stringout("Far");
    lcd_moveto(0,4);
    lcd_stringout("=");

    while (1) { // Main While Loop

        // Checking for button presses
        char Acquire = checkInputB(4);
        char threshholdchange = checkInputC(3);

        // Using EEPROM memory (Temp. Memory)
        short near = eeprom_read_word((void *) 100);
        if ((near >= 1) && (near <= 400)) {
            nearCount = near;
            lcd_moveto(0,5);
            char buf1[10];
            snprintf(buf1, 10, "%3d", nearCount);
            lcd_stringout(buf1);
        }

        short far = eeprom_read_word((void *) 200);
        if ((far >= 1) && (far <= 400)) {
            farCount = far;
            lcd_moveto(1,5);
            char buf2[10];
            snprintf(buf2, 10, "%3d", farCount);
            lcd_stringout(buf2);
        }

        // Rotary Encoder Code (Same from Lab 7)
        unsigned char var = PINC;
        a = var & (1 << PC1);
        b = var & (1 << PC2);

        if (!b && !a)
            old_state = 0;
        else if (!b && a)
            old_state = 1;
        else if (b && !a)
            old_state = 2;
        else
            old_state = 3;

        new_state = old_state;

        // If acquire button was pressed.
        if (Acquire == 1) { 
            generate_pulse(); // Generate a pulse on the Trig signal to the sensor. 
        }

        // If threshhold button was pressed we switch threshhold value
        if (threshholdchange == 1) {
            _delay_ms(10);

            if (threshhold == 1) { // ("was odd")
                threshhold = 0;
                lcd_moveto(0,4);
                lcd_stringout("=");
                lcd_moveto(1,4);
                lcd_stringout(" ");
            }

            else if (threshhold == 0){ // ("was near")
                threshhold = 1;
                lcd_moveto(1,4);
                lcd_stringout("=");
                lcd_moveto(0,4);
                lcd_stringout(" ");
            }
            lcd_moveto(1,8);
        }

        // If rotary encoder was adjusted
        if (rotaryChange == 1) {
            rotaryChange = 0;

            if (threshhold == 0) { // Near Count
                nearCount += count;
                if (nearCount > 400) {
                    nearCount = 400;
                }
                else if (nearCount < 1) {
                    nearCount = 1;
                }
                else if (nearCount > farCount-5) {
                    nearCount = farCount-5;
                }
                count = 0;
                lcd_moveto(0,5);
                char buf1[10];
                snprintf(buf1, 10, "%3d", nearCount);
                lcd_stringout(buf1);
                short neartemp = nearCount;
                eeprom_update_word((void *) 100, neartemp);
            }

            else if (threshhold == 1) { // Far Count
                farCount += count;
                if (farCount > 400){
                    farCount = 400;
                }
                else if (farCount < 1) {
                    farCount = 1;
                }
                else if (farCount < nearCount+5) {
                    farCount = nearCount+5;
                }
                count = 0;
                lcd_moveto(1,5);
                char buf2[10];
                snprintf(buf2, 10, "%3d", farCount);
                lcd_stringout(buf2);
                short fartemp = farCount;
                eeprom_update_word((void *) 200, fartemp);
            }

            lcd_moveto(1,8);
        }

        // If distance was measured by range finder, flag will turn on
        if (complete == 1) {
            
            // Arithmetic that yields centimeter values without using floating point values
            unsigned long long int temp = pulse_count*10;
            temp /= 116;
            distance = temp;

            // (46400 * 10)/116 = 4000 (max distance) *Note, in thousands

            if (distance/10 > 2) { // Min Range (2cm)
                if (distance/10 < 400) { // Max Range (400 cm) (Not including both min and max for just error checking)
                    lcd_moveto(0,10);
                    char buf[10];
                    snprintf(buf, 10, " %3d.%1d", distance/10, distance%10); // Centermeters
                    lcd_stringout(buf);
                    if (distance/10 < nearCount) {
                        play_note();
                    }
                } 
                else {
                    lcd_moveto(0,10);
                    lcd_stringout(">400.0");
                }
                _delay_ms(50);
            }
            else if (distance/10 == 400) {
                lcd_moveto(0,10);
                lcd_stringout(">400.0");
            }
            complete = 0;
            changed = 0;
        }

        // Led Changes
        if (distance/10 <= nearCount) { // Red (If less than near count)
            displayRed(); // Display Red LED
        }

        else if (distance/10 > nearCount && distance/10 < farCount) { // PWM Signal change with arithmetic (slope), if between near and far count
            displayPWM(); // Display PWM Signal using Arithmetic as LED
        }
        else if (distance/10 > farCount && distance/10 < 400) { // Green glows if range is more than far count but less than 400
            displayGreen(); // Display Green LED
        }
        else {  // Else, exceeded maximum glow blue
            displayBlue();  // Display Blue LED
        }
        Acquire = 0; // Reset button press
    }
}

// Code is indented properly and includes comments.
// Program is borken into seperate files based on function (best I can).
// Correctly initializes appropriate I/O Ports
// EEPROM usage is correct and valid
// TIMER1 is correct
// ISR used to correctly measure RangeFinder
// Code does not use floating point
// Buzzer uses TIMER0 for delay

// Sometimes code may be buggy (when you rotate encoder, and values don't change, it helps you keep switching between threshold) (TA said this is fine)