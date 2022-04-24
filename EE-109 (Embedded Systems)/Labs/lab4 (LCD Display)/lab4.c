/********************************************
*
*  Name: Paul Kim
*  Email: pbkim@usc.edu
*  Section: Wednesday (12:30 - 1:50)
*  Assignment: Lab 4 - Up/Down counter on LCD display
*
********************************************/

#include <avr/io.h>
#include <util/delay.h> // Libraries

#include "lcd.h"

enum states { UP, DOWN };



int main(void) {

    // Setup DDR and PORT bits for the 2 input buttons as necessary
    lcd_init();// Initialize the LCD

    // Enabling Pull-Up Resistors
    PORTC |= ((1 << 4)|(1 << 2));

    //Declaring variables
    char currentcount = 0;
    char statevariable = UP; // Start off in the UP direction.
    char loop = 0;

    lcd_writecommand(1); // Clears LCD

    // Use a state machine approach to organize your code
    //   - Declare and initialize a variable to track what state you
    //     are in by assigning the values UP or DOWN to that variable.

    while (1) {   // Loop forever
        // Changes States depending on button presses
        if ((PINC & (1 << 4)) == 0x00) { // LEFT MOST BUTTON = UP
            statevariable = UP;
        } 
        else if ((PINC & (1 << 2)) == 0x00) { // RIGHT MOST BUTTON = DOWN
            statevariable = DOWN;
        }

        // Condition for instant button presses
        if (loop == 50){
            loop = 0;
            if (statevariable == UP) { // If state=UP, counts UP
                currentcount++;
                if (currentcount == 10){ // 0-9
                    currentcount = 0;
                }
                lcd_writecommand(2);
                lcd_writedata(currentcount + '0'); // We do this for ASCII
            }

            else if(statevariable == DOWN) { // If state=DOWN, counts DOWN
                currentcount--;
                if (currentcount == -1){ // 0-9
                    currentcount = 9;
                }
                lcd_writecommand(2);
                lcd_writedata(currentcount + '0');
            }
        }

        loop++; // Iteration for instant button presses 


        // Use an outer if statement to select what state you are in
        // Then inside each 'if' or 'else' block, perform the desired
        // output operations and then sample the inputs to update
        // the state for the next iteration


        // Delay before we go to the next iteration of the loop
        _delay_ms(10);
    }

    return 0;   /* never reached */

    // Proper Comments Added
}

