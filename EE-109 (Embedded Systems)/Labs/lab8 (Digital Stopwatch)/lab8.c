/********************************************
 *
 *  Name: Paul Kim
 *  Email: pbkim@usc.edu
 *  Section: Wednesday 12:30 PM
 *  Assignment: Lab 8 - Digital Stopwatch
 *
 ********************************************/

// Including Useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "adc.h"

volatile unsigned char changed = 0; // Flag
volatile unsigned char num1 = '0';
volatile unsigned char num2 = '0';
volatile unsigned char num3 = '0';
volatile int state = 0;
// State 0 = Stopped, State 1 = Started, State 2 = Lapped

int main(void) {
    //Initializing LCD
    lcd_init();

    // Initializing ADC
    adc_init();

    // Writing splash screen
    lcd_writecommand(1); 
    lcd_moveto(0,4);
    lcd_stringout("Paul Kim");

    // Initializing Counter/Timer
    TCCR1B |= (1 << WGM12); // Setting mode to CTC mode
    TIMSK1 |= (1 << OCIE1A); // Enabling Timer Interrupt
    // We want a 100msOCR1A
    OCR1A = 6250; // Loading the 16 bit Counter Modulus into 
    TCCR1B |= (1 << CS12); // Setting Pre-Scalar to 256 (I WANT THIS GUY TO BE 8)
    TCCR1B &= ~((1 << CS11)|(1 << CS10));

    // (16,000,000 * 0.1)/256 = 6250
    // Get an interrupt for 0.1s


    sei(); // Enabling Interrupts

    // Splash Screen
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

    lcd_moveto(0,0);
    lcd_stringout("0.00");


    while(1) { // Loop Forever

        // Poll the ADC for button presses.
        // Updates the state of the stopwatch as needed
        // Checks a flag variable to see if an update of the displayed time on the LCD is required.

        unsigned char result = adc_sample(0);

        if (result >= 46 && result <= 56) { // Up Button
            while(result >= 46 && result <= 56) {
                result = adc_sample(0);
            }
            _delay_ms(100); // To handle debouncing
            if (state == 0) {
                state = 1;
            }
            else if(state == 1) {
                state = 0;
            }
            else if(state == 2) {
                state = 1;
            }
        }

        else if (result >= 97 && result <= 107) { // Bottom Button
            while(result >= 97 && result <= 107) {
                result = adc_sample(0);
            }
            _delay_ms(100); // To handle debouncing
            if (state == 0) {
                lcd_moveto(0,0);
                lcd_stringout("00.0");
                num1 = '0';
                num2 = '0';
                num3 = '0';
            }
            else if (state == 1) {
                state = 2;
            }
            else if (state == 2) {
                state = 1;
            }
        }

        if (changed && state == 1) { // If flag is changed and state is not stopped
            changed = 0;

            if (state == 2) {
                continue; // Should skip snprintf statements since lapped doesn't update count
            }

            char buffer[5];
            // We need to manually change buffer since we use three number variables
            lcd_moveto(0,0);
            buffer[0] = num1;
            buffer[1] = num2;
            buffer[2] = '.';
            buffer[3] = num3;
            buffer[4] = '\0'; // Null Character
            lcd_stringout(buffer);
        }
    }

}
ISR(TIMER1_COMPA_vect) { // Should generate an interrupt every 0.1 seconds
    // Timer that increments every 0.1s

    if (state == 0) { // When stopped
        // Do nothing here
    }
    else {
        if (num1 == '5' && num2 == '9' && num3 == '9') { // Timer resets to 0.0 at 59.9 seconds
            num1 = '0';
            num2 = '0';
            num3 = '0';
        }
        else {
            if (num3 == '9') { // Changes to 0 if at digit 9
                if (num2 == '9') {
                    num2 = '0';
                    num3 = '0';
                    num1++;
                }
                else {
                    num3 = '0';
                    num2++;
                } 
            }
            else {
                num3++;
            }
            
        }
        changed = 1; // If change then flag should change.
    }
}