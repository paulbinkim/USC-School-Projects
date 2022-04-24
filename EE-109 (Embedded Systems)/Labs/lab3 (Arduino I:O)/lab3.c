/********************************************
*
*  Name: Paul Kim
*  Email: pbkim@usc.edu
*  Lab section: Wednesday (12:30 PM)
*  Assignment: Lab 3
*
********************************************/

#include <avr/io.h> // Including useful libraries
#include <util/delay.h>

#define DOT_LENGTH  250         /* Define the length of a "dot" time in msec */

void dot(void); // Declaring prototypes
void dash(void);
void makeOutput(char);
char checkInput(char);

int main(void)
{

    // Initialize appropriate DDR registers
    DDRD |= (1 << 2);
    DDRB &= ~((1 << 3)|(1 << 4)|(1 << 5));

    // Initialize the LED output to 0
    PORTD &= ~(1 << 2);

    // Enable the pull-up resistors for the 3 button inputs 
    PORTB |= ((1 << 3)|(1 << 4)|(1 << 5));
	
    // Main while statement for USC output
    while (1) {   
      char Input = checkInput(3); // Checks input of button 1,2,3
      char Input2 = checkInput(4);
      char Input3 = checkInput(5);
      
      if (Input == 1) { // Prints U in morse code
        dot();
        dot();
        dash();
        _delay_ms(DOT_LENGTH*3); // Dash Delay
      }

      if (Input2 == 1) { // Prints S in morse code
        dot();
        dot();
        dot();
        _delay_ms(DOT_LENGTH*3); // Dash Delay
      }

      if (Input3 == 1) { // Prints C in morse code
        dash();
        dot();
        dash();
        dot();
        _delay_ms(DOT_LENGTH*3); // Dash Delay
      }
    }
	//  Use if statements and the checkInput()
	//  function to determine if a button
	//  is being pressed and then output
	//  the correct dot/dash sequence by
	//  calling the dot(), dash(), and 
	//  using appropriate delay functions

    return 0;   /* never reached */
}

/*
  dot() - Makes the output LED blink a "dot".

  Write code to generate a dot by using the makeOutput function
  to turn the output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay an
  appropriate time after you turn the output off
*/
void dot() // Check*****
{
  makeOutput(1);
  _delay_ms(DOT_LENGTH); // Delay
  makeOutput(0);
  _delay_ms(DOT_LENGTH);
}

/*
  dash() - Makes the output LED blink a "dash".

  Write code to generate a dash by using the makeOutput function
  to turn the output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay
  appropriate time after you turn the output off
*/
void dash() // Check****
{
  // *Dashes are 3 times longer than a dot
  makeOutput(1);
  _delay_ms(DOT_LENGTH*3); // Delay (3x of dot length)
  makeOutput(0);
  _delay_ms(DOT_LENGTH*3);
}

/*
  makeOutput() - Changes the output bit to either a zero 
  or one, based on the input argument "value".
  
  If the argument is zero, turn the output OFF,
  otherwise turn the output ON. 
  
  Do not use any delays here.  Just use bit-wise operations
  to make the appropriate PORT bit turn on or off.
*/
void makeOutput(char value)
{
  if (value == 0x00) {  // Changes output based on value (if 0 or 1)
    PORTD &= ~(1 << 2);
  }
  else {
    PORTD |= (1 << 2);
  }
}

/*
  checkInput(bit) - Checks the state of the input bit specified by the
  "bit" argument (0-7), and returns either 0 or 1 depending on its state.
  
  Write code to use the appropriate group's PIN register and determine if  
  the specified bit (which is passed as the argument) of that group is
  pressed or not.  Think carefully about what bit value means "pressed"
  when connected to a pushbutton.
 */
char checkInput(char bit)
{
  if ((PINB & (1 << bit)) == 0x00) { // Checks if PINB is either 0 or 1
    return 1; // Button is pressed
  }
  else {
    return 0; // Button is not pressed
  }
}
