// Including useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "buzzer.h"
#include "finalproject.h"

// Declaring volatile variables
volatile unsigned char speakerState = 0; // State for Buzzer
volatile int buzzerCount = 0; // Used for Buzzer

// Initializing Buzzer Registers
void buzzer_init() {
	// Buzzer Timer
    DDRC |= (1 << PC5); // Setting buzzer for output
    PORTC &= ~(1 << 5);
}

// Start of Buzzer
ISR(TIMER0_COMPA_vect) { // Timer 0 for buzzer
    if (speakerState == 0) {
        speakerState = 1;
        PORTC |= (1 << 5); // (Output)
    }
    else {
        speakerState = 0;
        PORTC &= ~(1 << 5); // (Stop Output)
    }
    buzzerCount++;

    if (buzzerCount == 248) { // 1 second (hopefully)
        TCCR0B &= ~(1 << CS02); // 1/64 Prescale Clock
        buzzerCount = 0;
    }
}

// Plays a sound at a certain frequency
void play_note() {
    TCCR0A |= (1 << WGM01); // Set the CTC Mode (TIMER 0)
    TIMSK0 |= (1 << OCIE0A); // Timer Interrupt (0)
    OCR0A |= 250; // (8 bits)
    TCCR0B |= (1 << CS02); // 256 Prescale Clock
}

// End of Buzzer