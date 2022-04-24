// Including Useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "finalproject.h"
#include "encoder.h"

// Declaring Volatile Variables
volatile unsigned char new_state, old_state; // Rotary States (Used from Lab 7)
volatile unsigned char rotaryChange = 0; // Rotary Flag
volatile int count = 0; // Rotary ISR will be summed
volatile unsigned char a, b; // Used for Rotary Encoder

// Code that initializes Rotary Encoder Registers
void rotary_init() {
	DDRC &= ~((1 << PC1)|(1 << PC2)); // Making PORT C1 and PORT C5 to input (Set to 0) (Rotary)
    PORTC |= ((1 << PC1)|(1 << PC2)); // Enabling Pull-Up Resistors for PC 1 and PC 2

    PCICR |= (1 << PCIE1); // Enable PORTD Interrupt and PORTC Interrupt
    PCMSK1 |= ((1 << PCINT9)|(1 << PCINT10)); // Interrupt Mask (PC1, PC2)
}

// Start of Rotary Encoder
ISR(PCINT1_vect) {
    // Copied Exact State Diagram from lab7
    unsigned char var = PINC;
    a = var & (1 << PC1);
    b = var & (1 << PC2); 

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
        rotaryChange = 1;
        old_state = new_state;
    }
}
// End of Rotary Encoder