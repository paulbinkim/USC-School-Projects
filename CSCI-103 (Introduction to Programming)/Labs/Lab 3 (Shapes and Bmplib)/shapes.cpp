#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
  
  if (top < 0 || left < 0) { // Statements if top/left value is negative.
    if (top < 0) {
      height = height + top; // Essentially just subtracts the difference, and makes drawing start at 0.
      top = 0;
    }
    else if (left < 0) {
      width = width + left;
      left = 0;
    }
  }
  
  if ((width + left) > 256) { // Statement if width+left goes beyond the right side.
    width = 256 - left;
  }
  if ((height + top) > 256) { // Statement if height+top goes beyond the bottom.
    height = 256 - top;
  }
  
  for (int i = 0; i <= height; i++) { // Making Rectangle (Filled) starting at top and left
    for (int z = 0; z <= width; z++) {
      image [i + top][z + left] = 0;
    }
  }
  
  for (int i = 1; i <= (height-1); i++) { // Making Rectangle Hollow
    for (int z = 1; z <= (width-1); z++) {
      image [i + top][z + left] = 255;
    }
  }
}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) { // Ellipse Function
  double h = height/2;
  double w = width/2;
   for (double theta=0.0; theta < 2*M_PI; theta += .01) { // Every small iteration of 0.01.
     double x = w*cos(theta);
     double y = h*sin(theta);
     x += cx;
     y += cy; // Determine function from Demo.CPP
     
     int yposition = (int)y;
     int xposition = (int)x;
     
     if (xposition < 0 || yposition < 0) { // Part of code that makes ellipse not repeat.
     }
     else if (xposition > 256 || yposition > 256) { // If either the x or y position are off the graph
     }
     else {
       image[yposition][xposition] = 0; // Then the 2D array does not print the determined value.
     }
   }
}

int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }
   
   // Main program loop here
  int x = 0;
  int TR, TC, H, W;
  int CC, CR;
  
  // Repeating Menu
  while (x != 2) {
    cout << "Enter 0 to draw a rectangle" << endl;
    cout << "Enter 1 to draw an ellipse" << endl;
    cout << "To save your drawing as ""output.bmp"" and quit, please enter 2" << endl;
    
    cin >> x;
    
    if (x == 0) {
      cout << "Please enter TR (Top Row), TC (Left Column), H & W (Height and Width)" << endl;
      cin >> TR >> TC >> H >> W;
      draw_rectangle (TR, TC, H, W);
    }
    else if (x == 1) {
      cout << "Please enter CC (Column), CR (Center Row), H & W (Height and Width)" << endl;
      cin >> CC >> CR >> H >> W;
      draw_ellipse (CC, CR, H, W);
    }
    else if (x == 2) {
      break;
    }
    else {
      cout << "Invalid command, please try again" << endl;
    }
  }
   
   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);
   
   return 0;
}
