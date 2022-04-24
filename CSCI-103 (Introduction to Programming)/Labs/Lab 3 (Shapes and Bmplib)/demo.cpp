#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

int main() {
   unsigned char image[SIZE][SIZE];

   for (int i=0; i < SIZE; i++) { // Initializes all pixels to white.
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }

   for(int i=0; i < SIZE; i++) { // Makes a cross black.
      image[i][128] = 0;
      image[128][i] = 0;
   }
    
   for(int i=0; i < SIZE; i++) { // Makes Black Diagonal Line.
      image[i][i] = 0;
   }

   double r = 50;
   for (double theta=0.0; theta < 2*M_PI; theta += .01) { // Makes circle.
      double x = r*cos(theta);
      double y = r*sin(theta);
      x += SIZE/2;
      y += SIZE/2;
      image[(int)y][(int)x] = 0;
   }
     
   // save to file
  
   writeGSBMP("cross.bmp", image);
   return 0;
}
