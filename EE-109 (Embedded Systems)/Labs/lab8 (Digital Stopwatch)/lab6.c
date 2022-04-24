/********************************************
 *
 *  Name: Paul Kim 
 *  Email: pbkim@usc.edu
 *  Section: Wednesday 12:30
 *  Assignment: Lab 6 - Analog-to-digital conversion
 *
 ********************************************/

// Including Useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "adc.h"

void rand_init(void); // rand_int prototype

int main(void)
{
    // Initialize the LCD
    lcd_init();

    // Initialize the ADC
    adc_init();

    // Initialize the random number function
    rand_init();

    // Writing splash screen
    lcd_writecommand(1); 
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

    // Finding a random initial position of the 'X' and checking for Potentiomeer signal.
    int position = rand()%15; // Random position of X.
    int PotPosition = adc_sample(3)/17; // Divides by 17 because 255 / 15 spots.

    // Display the 'X' and '^' on the screen
    lcd_moveto(0, position);
    lcd_stringout("X");

    lcd_moveto(1,PotPosition);
    lcd_stringout("^");

    int count = 0; // Counter for 2 second condtion if X = ^

    while (1) { // Loop forever
        unsigned char result = adc_sample(0); // Sample 0 checks for button presses.

        // Checking if button is pressed and if pressed, moving X to new position

        if (result > 151 && result < 161) { // Left Button Range
            if (position != 0) {
                 position -= 1;
            }
            lcd_moveto(0, position+1); // Output statements (checks edge case)
            lcd_stringout(" ");
            lcd_moveto(0, position);
            lcd_stringout("X");
            _delay_ms(250);
        }

        else if (result >=0 && result < 5) { // Right Button Range
            if (position != 15) {
                position += 1;
            }
            lcd_moveto(0, position-1); // Output statements (check edge case)
            lcd_stringout(" ");
            lcd_moveto(0, position);
            lcd_stringout("X");
            _delay_ms(250);
        }

        unsigned char PotResult = adc_sample(3); // Sample 3 checks for potentiometer signal values.
        PotResult /= 17; // 255/15 spaces = range 17.

        if (PotResult != PotPosition) { // If Potentiometer signals and respective positions are different.
            lcd_moveto(1, PotPosition);
            lcd_stringout(" ");
            lcd_moveto(1, PotResult);
            lcd_stringout("^");

            PotPosition = PotResult;
            _delay_ms(10);
        }

        if (PotResult == position) { // If X = ^
            count++;
            _delay_ms(10);
            if (count >= 200) { // Here, we want a 2 second stamp that indicates success.
                lcd_writecommand(1);
                lcd_moveto(0,2);
                lcd_stringout("You have won");
                lcd_moveto(1,3);
                lcd_stringout("the game!");
                break;
            } 
        }
        else { // Else, reset, it was only moving past.
                count = 0;
            }
    }
    return 0;   /* never reached */
}

void rand_init() // Random init function that uses a seed.
{
    int seed = 0;
    unsigned char i, j, x;

    // Build a 15-bit number from the LSBs of an ADC
    // conversion of the channels 1-5, 3 times each
    for (i = 0; i < 3; i++) {
	for (j = 1; j < 6; j++) {
	    x = adc_sample(j);
	    x &= 1;	// Get the LSB of the result
	    seed = (seed << 1) + x; // Build up the 15-bit result
	}
    }
    srand(seed);	// Seed the rand function
}
