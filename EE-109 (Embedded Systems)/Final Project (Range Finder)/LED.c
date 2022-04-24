// Including useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "LED.h"
#include "finalproject.h"
#include "lcd.h"

// Function that displays Red
void displayRed() {
	PORTC &= ~(1 << 4);
	OCR2A = 0;
}

// Function that displays a PWM signal using proper arithmetic
void displayPWM() {
	PORTC &= ~(1 << 4);
    double slope = ((255.0)/(farCount-nearCount));
    double yInt = slope*nearCount;
    int tempOCR2A = ((distance/10)*slope)-yInt;
    OCR2A = tempOCR2A;
}

// Function that displays Green
void displayGreen() {
	PORTC &= ~(1 << 4);
    OCR2A = 255;	
}

// Function that displays Blue
void displayBlue(){
	OCR2A = 0;
    PORTC |= (1 << 4);
    PORTB &= ~(1 << 3);
}

// Function that initializes all LED registers
void LED_init() {
	// LED PWM Signal (Stated on Prompt)
    TCCR2A |= (1 << COM2A1);
    TCCR2A |= ((1 << WGM21)|(1 << WGM20));
    TCCR2B |= (1 << CS22);
    OCR2A = 128;
    DDRB |= (1 << PB3);
    DDRC |= (1 << PC4);
}