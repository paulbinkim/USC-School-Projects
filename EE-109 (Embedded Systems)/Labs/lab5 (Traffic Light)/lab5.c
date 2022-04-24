/********************************************
*
*  Name: Paul Kim
*  Email: pbkim@usc.edu
*  Section: Wednesday 12:30PM
*  Assignment: Lab 5 - Traffic light
*
********************************************/

#include <avr/io.h> // Including Libraries
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"

enum states { MAIN1, MAIN2, LEFT1, LEFT2, SMALL1, SMALL2 }; // States 

int main(void) {

   // CODE FOR SPLASH SCREEN AT START UP

   /* Call lcd_init to set up the LCD */
   lcd_init();

   // Clears LCD
   lcd_writecommand(1); 

   /* Set up I/O ports for buttons */
   PORTC |= ((1 << 1)|(1 << 2)|(1 << 3)|(1 << 4)); // Pull-up Resistors
   DDRC &= ~((1 << 1)|(1 << 2)|(1 << 3)|(1 << 4)); // Set to Input

   /* Call lcd_stringout to print out your name */
   lcd_stringout("Paul Kim");

   /* Use snprintf to create a string with your birthdate */
   char date[30];
   int month = 2;
   int day = 7;
   int year = 2002;
   snprintf(date, 30, "%02d/%02d/%d", month, day, year); // Formatting using snprintf

   /* Use lcd_moveto to start at an appropriate column 
       in the bottom row to appear centered */
   lcd_moveto(1,3);

   /* Use lcd_stringout to print the birthdate string */
   lcd_stringout(date);

   /* Delay 1 second */
   _delay_ms(1000);

   /* Initialize State machine variables */

   int leftturn = 0; // If 1, should make make LEFT = G, and all else red (Left signal is on)
   int smallturn = 0; // If 1, should make SMALL = G, and all else red (Right signal is on)

   int counter = 10; // Initialized to 10, for this program only, because of the delay of my loop (self-implementation decision)
   unsigned char state = MAIN1; // State variable, initialized to MAIN1

   lcd_writecommand(1); // Clear LCD

   // MAIN CODE FOR TRAFFIC CONTROLLER FUNCTION

   while(1)
   { 
      /* Read the sensors (Buttons) */
      // Reads at a fast rate because no counter is used here.

      if ((PINC & (1 << 1)) == 0x00) { // LEFT 1 is pressed
         leftturn = 1;
         lcd_moveto(1,8);
         lcd_stringout("L");
      }
      else {
         lcd_moveto(1,8); // Clears instant
         lcd_stringout(" ");
      }

      if ((PINC & (1 << 2)) == 0x00) { // LEFT 2 is pressed
         leftturn = 1;
         lcd_moveto(1,9);
         lcd_stringout("L");
      }
      else {
         lcd_moveto(1,9);
         lcd_stringout(" ");
      }

      if ((PINC & (1 << 3)) == 0x00) { // SMALL 1 is pressed
         smallturn = 1;
         lcd_moveto(1,10);
         lcd_stringout("S");
      }
      else {
         lcd_moveto(1,10);
         lcd_stringout(" ");
      }

      if ((PINC & (1 << 4)) == 0x00) { // SMALL 2 is pressed
         smallturn = 1;
         lcd_moveto(1,11);
         lcd_stringout("S");
      }
      else {
         lcd_moveto(1,11);
         lcd_stringout(" ");
      }

      /* Determine new state (Using State Diagram) */ 
      
      if (counter == 10) { // Counter 10 to fix flickering (interates from 0, other than intial start of 10)

         if (state == MAIN1) {
            state = MAIN2;
         }

         else if (state == MAIN2) {
            if (leftturn == 1) {
               state = LEFT1;
               leftturn = 0;
            }
            else if (smallturn == 1 && leftturn != 1) {
               state = SMALL1;
               smallturn = 0;
            }
         }

         else if (state == LEFT1) {
            if (smallturn == 1) {
               state = SMALL2;
               smallturn = 0;
               leftturn = 0;
            }
            else {
               state = MAIN1;
               leftturn = 0;
            }
         }

         else if (state == SMALL1) {
            if (leftturn == 1) {
               state = LEFT2;
               leftturn = 0;
               smallturn = 0;
            }
            else {
               state = MAIN1;
               smallturn = 0;
            }
         }

         else if (state == LEFT2 || state == SMALL2) {
            state = MAIN1;
            leftturn = 0;
            smallturn = 0;
         }
      }

      /* Show outputs */
      // Initializing variables (lights) and buffers
      char bufML[7];
      char bufS[8];
      char MAIN = 'G';
      char LEFT = 'R';
      char SMALL = 'R';

      if (counter == 10) {

         if (state == MAIN1 || state == MAIN2) { // If Main State
            MAIN = 'G';
            LEFT = 'R';
            SMALL = 'R';
         }

         else if (state == LEFT1 || state == LEFT2) { // If Left State
            MAIN = 'R';
            LEFT = 'G';
            SMALL = 'R';
         }

         else if (state == SMALL1 || state == SMALL2) { // If Small State
            MAIN = 'R';
            LEFT = 'R';
            SMALL = 'G';
         }

         // Using SNPRINTF to format buffer
         lcd_moveto(0,0);
         snprintf(bufML, 7, "MAIN=%c", MAIN);
         lcd_stringout(bufML);

         lcd_moveto(1,0);;
         snprintf(bufML, 7, "LEFT=%c", LEFT);
         lcd_stringout(bufML);

         lcd_moveto(0,8);
         snprintf(bufS, 8, "SMALL=%c", SMALL);
         lcd_stringout(bufS);
         
         counter = 0;
      }  
      _delay_ms(200); // DELAY (only one)
      counter++;
   }

   return 0;   /* never reached */
}