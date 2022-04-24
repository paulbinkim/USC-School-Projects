// Including useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "rangefinder.h"
#include "finalproject.h"


// Declaring volatile variables
volatile unsigned char changed = 0; // Flag for Range Finder
volatile unsigned char complete = 0; // Flag for Range Finder (Indicating Measurement was captured)
volatile unsigned long long int pulse_count = 0; // Used to capture Range Finder Count
volatile unsigned char threshhold = 0; // 0 is when Threshhold is set to near, 1 when far

// Intializing Range Registers
void range_init() {
	// Range Finder Timer
	DDRD |= (1 << 2); // PD2 is Output for Trigger
    DDRD &= ~(1 << 3); // PD3 is Input for Echo

    TCCR1B |= (1 << WGM12); // Setting mode to CTC mode
    OCR1A = 46400;// Loading 16 bit counter modulus (400 cm = 23,000 microseconds)
    TIMSK1 |= (1 << OCIE1A); // Enabling Timer Interrupt   

    PCICR |= (1 << PCIE2); // Enable PORTD Interrupt and PORTC Interrupt
    PCMSK2 |= (1 << PCINT19); // Interrupt Mask (PD3)
}

// Start of Range Finder
ISR(PCINT2_vect) { // PORTD Interrupt
    // check if echo bit is high
    // else if echo is low, went high to low

    // Determine whether its detecting the start of the pulse (0 timer count,), or the end of a pulse
    //  stop timer, set flag that measurement complete.

    if (changed == 0) {
        complete = 0;
        TCNT1 = 0;
        TCCR1B |= (1 << CS11); // Prescalar of 8
        TCCR1B &= ~((1 << CS12)|(1 << CS10)); // Prescalar of 8
        changed = 1; // Start
    }
    else {
        TCCR1B &= ~(1 << CS11); // Stop counter
        pulse_count = TCNT1; // Save count
        complete = 1;
    }
}

ISR (TIMER1_COMPA_vect) { // Stops when max amount occurs (Watch Dog Timer) (this ISR will be invoked if out of range)
    TCCR1B &= ~(1 << CS11); // Stop counter
    pulse_count = 46400;
    complete = 1;
}
// End of Range Finder