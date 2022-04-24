#include <avr/io.h> // Including Useful Libraries
#include "adc.h"

void adc_init(void) // ADC initialization function called in lab6.c
{
    ADMUX &= 0x00; // Clears all bits to 0
    ADCSRA &= 0x00; // Clears all bits to 0

    //Implicitily setting Ref S1 to 0
    ADMUX |= ((1 << 6)|(1 << 5)); // Setting ADLAR and REFS0 to 1
    ADCSRA |= ((1 << 7)|(1 << 2)|(1 << 1)|(1 << 0)); // Setting proper values in ADCSRA
}

unsigned char adc_sample(unsigned char channel) // ADC sample function called in lab6.c
{
    // Set ADC input mux bits to 'channel' value
    // Convert an analog input and return the 8-bit result

    // Copying Channel bits into ADMUX

    ADMUX &= ~(0x0F); // Creating mask and clearing bits
    ADMUX |= (channel & 0x0F);

    // Starting a sample

    ADCSRA |= (1 << 6);  // Setting ADSC bit to 1

    // Wait for ADC to indicate the sample is ready

    while (((ADCSRA & (1 << 6)) != 0)); // Blank while loop that waits until 1 (TA said this is fine).

    // Retrieve and returning the sample
    unsigned char result = ADCH;
    return result; 
}