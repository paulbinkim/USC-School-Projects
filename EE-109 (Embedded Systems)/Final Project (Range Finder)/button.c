// Including Useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "button.h"
#include "finalproject.h"
	
// Function that checks input for Button (B) (Acquire)
char checkInputB(char bit) {
	if ((PINB & (1 << bit)) == 0x00) { // Checks if PINB is either 0 or 1
    	_delay_ms(5);
    	while ((PINB & (1 << bit)) != 0);
    	_delay_ms(5);
    	return 1; // Button is pressed
  	}
  	else {
    	return 0; // Button is not pressed
	}
}

// Function that checks input for Button (C) (Threshold)
char checkInputC(char bit) {
	if ((PINC & (1 << bit)) == 0x00) { // Checks if PINB is either 0 or 1
    	_delay_ms(50);
    	while ((PINC & (1 << bit)) != 0);
    	_delay_ms(50);
    	return 1; // Button is pressed
  	}
  	else {
    	return 0; // Button is not pressed
  	}
}

// Function that generates a pulse
void generate_pulse() {
	PORTD |= (1 << 2); 
    _delay_us(10); // Specific Time
    PORTD &= ~(1 << 2);
}

// Function that initializes Button registers
void button_init() {
	// Setting appropriate DDR registers and enabling pull up resistors for the buttons.
    DDRB &= ~(1 << 4); // Aqcuire Button (As Input)
    DDRC &= ~(1 << 3); // Threshhold Button as Input
    PORTB |= (1 << 4); // Pullup Resitors
    PORTC |= (1 << 3); // Pullup Resistor
}