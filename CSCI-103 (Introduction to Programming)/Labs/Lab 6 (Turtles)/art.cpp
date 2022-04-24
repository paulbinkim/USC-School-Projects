#include "draw.h"
#include "turtle.h"
#include <cmath>
#include <iostream>

using namespace std;

int main() {
   draw::setpenwidth(5);
   draw::setrange(-100, 100);

   // Turtle 1 (Red)
   Turtle Tim(30, 25, 240); 
   Tim.setColor(draw::RED);
  
   // Turtle 2 (Blue)
   Turtle Peter (0, 0 , 70);
   Peter.setColor(draw::BLUE);
   
   // Turtle 3 (Pink)
   Turtle Robert (20, 20, 10);
   Robert.setColor(draw::PINK);
  
   // Turtle 4 (Coral)
   Turtle Mike (-30, -30, 0);
   Mike.setColor(draw::CORAL);
   
   for (int i = 0; i < 5; i++) {
     Tim.move(50);
     Tim.turn(-105);
     draw::show(50);
     Peter.move(30);  
     Peter.turn(140); 
     draw::show(50);
     Robert.move(25);  
     Robert.turn(25); 
     draw::show(50);
     Mike.move(15);  
     Mike.turn(-50); 
     draw::show(50);
   }

   return 0;
}

