/********************************************
 *
 *  Name: Paul Kim
 *  Email: pbkim@usc.edu
 *  Section: Wednesday 12:30 PM
 *  Assignment: Lab 7 - Rotary Encoder
 *
 ********************************************/

// Including Useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcd.h"

// Prototypes for functions
void variable_delay_us(int);
void play_note(unsigned short);

// Frequencies for natural notes from middle C (C4)
// up one octave to C5.
unsigned short frequency[8] =
	{ 262, 294, 330, 349, 392, 440, 494, 523 };

// Global Variables
volatile unsigned char new_state, old_state;
volatile unsigned char changed = 0;  // Flag for state change
volatile int count = 0;		// Count to display (Signed Variable)
volatile unsigned char a, b;

int main(void) {
    // Initializing DDR and PORT registers and LCD
    lcd_init();
    DDRC &= ~((1 << PC1)|(1 << PC5)); // Making PORT C1 and PORT C5 to input (Set to 0)
    DDRB |= (1 << PC4); // Setting buzzer for output (Set to 1)
    PORTC |= ((1 << PC1)|(1 << PC5)); // Enabling Pull-Up Resistors for PC 1 and PC 2
    PORTB &= ~(1 << 4);

    // Writing a splash screen to the LCD
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

    // Reading the A and B inputs to determine the intial state.
    // In the state number, B is the MSB and A is the LSB. (Highest Digit, Lowest Digit)
    // Warning: Do NOT read A and B separately.  You should read BOTH inputs
    // at the same time, then determine the A and B values from that value.    

    // We must put PINC into a variable (Review Question)
    unsigned char var = PINC;
    a = var & (1 << PC1);
    b = var & (1 << PC5);

    if (!b && !a)
		old_state = 0;
    else if (!b && a)
		old_state = 1;
    else if (b && !a)
		old_state = 2;
    else
		old_state = 3;

    new_state = old_state;

    // Initializing Interrupts
    PCICR |= (1 << PCIE1);
    PCMSK1 |= ((1 << PCINT9)|(1 << PCINT13));
    sei(); // Enabling Global Interrupts

    // Writing Generic EE Lab 7 Poll Statement
    lcd_moveto(0,0);
    lcd_stringout("EE109 Lab 7 Poll");

    // Writing Initial Count of 0
    lcd_moveto(1,3);
	char buffer[5];
	snprintf(buffer, 5, "%04d", count);
	lcd_stringout(buffer);

    while (1) { // Loop forever
	// Checking a flag change
	    if (changed) { // Did state change?
		    changed = 0; // Reset changed flag
		    // Output count to LCD
		    lcd_moveto(1,3);
		    char buffer[5];
		    snprintf(buffer, 5, "%04d", count);
		    lcd_stringout(buffer);
		}

		// Do we play a note?
		if ((count % 8) == 0) { // Plays for every modulus of 8
			// Determine which note (0-7) to play
			// Find the frequency of the note
			int note = (abs(count) % 64) / 8; // Equation from writeup
			// Call play_note and pass it the frequency
			play_note(frequency[note]);

		}
    }
}

// Interrupt Routine
ISR(PCINT1_vect) {

	unsigned char var = PINC; // We must put PINC into a variable
    a = var & (1 << PC1);
    b = var & (1 << PC5);

	// For each state, examine the two input bits to see if state
	// has changed, and if so set "new_state" to the new state,
	// and adjust the count value.
    // Copy the states above given.

	// 00 = State 0
	// 01 = State 1
	// 10 = State 2
	// 11 = State 3
	// Following State Diagram in Handout

	if (old_state == 0) {
	    // Handle A and B inputs for state 0
	    if (a) { // Clockwise
	    	new_state = 1;
	    	count++;
	    }
	    else if (b) { // Counter Clockwise
	    	new_state = 2;
	    	count--;
	    }
	}
	else if (old_state == 1) {

	    // Handle A and B inputs for state 1
	    if (b) {
	    	new_state = 3;
	    	count++;
	    }
	    else if (!a) { 
	    	new_state = 0;
	    	count--;
	    }

	}
	else if (old_state == 2) {

	    // Handle A and B inputs for state 2
	    if (!b) {
	    	new_state = 0;
	    	count++;
	    }
	    else if (a) {
	    	new_state = 3;
	    	count--;
	    }

	}
	else {   // old_state = 3

	    // Handle A and B inputs for state 3
	    if (!a) {
	    	new_state = 2;
	    	count++;
	    }
	    else if (!b) {
	    	new_state = 1;
	    	count--;
	    }

	}

	// If state changed, update the value of old_state,
	// and set a flag that the state has changed.
	// Determines if there was a change
	if (new_state != old_state) {
	    changed = 1;
	    old_state = new_state;
	}
}

/*
  Play a tone at the frequency specified for one second
*/
void play_note(unsigned short freq)
{
    unsigned long period;

    period = 1000000 / freq; // Period of note in microseconds

    while (freq--) {
		// Make PB4 high
	    PORTB |= (1 << PB4);

		// Use variable_delay_us to delay for half the period
		variable_delay_us(period/2);

		// Make PB4 low
		PORTB &= ~(1 << PB4);

		// Delay for half the period again
		variable_delay_us(period/2);
    }
}

/*
    variable_delay_us - Delay a variable number of microseconds
*/
void variable_delay_us(int delay)
{
    int i = (delay + 5) / 10;

    while (i--)
        _delay_us(10);
}
