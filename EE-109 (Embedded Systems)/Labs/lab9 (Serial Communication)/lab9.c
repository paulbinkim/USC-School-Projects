/********************************************
 *
 *  Name: Paul Kim
 *  Email: pbkim@usc.edu
 *  Section: Wednesday 12:30 PM
 *  Assignment: Lab 9 - Serial Communications
 *
 ********************************************/

//Including Useful Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "adc.h"

// Volatile Data Types
volatile unsigned char changed = 0; // Flag
volatile unsigned int counter = 0;
volatile char buffer[17];

// Serial communications functions and variables
void serial_init(unsigned short);
void serial_stringout(char *);
void serial_txchar(char);

#define FOSC 16000000           // Clock frequency
#define BAUD 9600               // Baud rate used
#define MYUBRR (FOSC/16/BAUD-1) // Value for UBRR0 register

char *messages[] = {
    "Hello           ",
    "How are you?    ",
    "What's up shawty",
    "What's Popping? ",
    "What's the move?",
    "Banana or Apple ",
    "HEHEHEHEHEHEHEHE",
    "I like turtle   ",
    "I love EE109    ",
    "Turquoise       ",
    "DOPE!           ",
    "Hi!             ",
    // At Least 10 Messages
};

int main(void) {

    // Initializing the LCD, ADC and serial modules
    lcd_init();
    adc_init();
    serial_init(MYUBRR); // Setting Baud Rate
    
    // Enabling interrupts
    UCSR0B |= (1 << RXCIE0); // Enabling receiver interrupts.
    sei();

    // Showing the splash screen
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

    // Initial LCD String Out
    unsigned char counter = 0;
    char buf[17];
    buf[16] = '\0';
    lcd_moveto(0,0);
    snprintf(buf, 17, "%s", messages[counter]);
    lcd_stringout(buf);

    while (1) {// Loop forever

	    // Get an ADC sample to read buttons
        unsigned char result = adc_sample(0);

        if (result >= 46 && result <= 56) { // Up Button is Pressed
            while (result >= 46 && result <= 56) {
                result = adc_sample(0);
            }
            _delay_ms(100); // To handle debouncing
            counter++;
            lcd_moveto(0,0);
            snprintf(buf, 17, "%s", messages[counter%12]);
            lcd_stringout(buf);
        }

        else if (result >= 97 && result <= 107) { // Down Button is Pressed
            while (result >= 97 && result <= 107) {
                result = adc_sample(0);
            }
            _delay_ms(100); // To handle debouncing
            counter--;
            lcd_moveto(0,0);
            snprintf(buf, 17, "%s", messages[counter%12]);
            lcd_stringout(buf);
        }

        else if (result >= 199 && result <= 213) { // Select Button is Pressed
            while (result >= 199 && result <= 213) {
                result = adc_sample(0);
            }
            _delay_ms(100); // To handle debouncing
            serial_stringout(messages[counter%12]); // Relay message to interrup
        }

        // Message received from remote device?
        if (changed == 1) { // Flag will be changed if interrupt transfer is complete.
            changed = 0;
            lcd_moveto(1,0);
            buffer[16] = '\0';
            snprintf(buf, 17, "%s", buffer);
            lcd_stringout(buf);
        }
    }
}

/* ----------------------------------------------------------------------- */

// ISR's and Interupts

void serial_init(unsigned short ubrr_value)
{
    // Setting up USART0 registers (Turn on Communications)
    UBRR0 = ubrr_value;
    UCSR0C = (3 << UCSZ00); // Async., no parity
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0); // Enabling RX and TX

    // Enabling the tri-state buffer
    DDRD |= (1 << 3); // Setting Port D3 as output
    PORTD &= ~(1 << 3); // Line to enable buffer
}

void serial_txchar(char ch)
{
    while ((UCSR0A & (1 << UDRE0)) == 0);
    UDR0 = ch;
}

void serial_stringout(char *s)
{
    // Call serial_txchar in loop to send a string
    // (Very similar to lcd_stringout in lcd.c)
    int i = 0;
    while (s[i] != '\0') {    // Loop until next charater is NULL byte
        serial_txchar(s[i]);  // Send the character
        i++;
    }
}

ISR(USART_RX_vect)
{
    // Handle received character
    char ch;
    ch = UDR0;

    buffer[counter] = ch;
    counter++;

    if (counter == 16) {
        counter = 0;
        buffer[16] = '\0';
        changed = 1;
    }
}
