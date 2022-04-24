//This file also starts out empty.
//Implement the Turtle class here.

#include "turtle.h" 
#include "draw.h"
#include <cmath>
#include <iostream>

using namespace std;

Turtle::Turtle(double x0, double y0, double dir0) {
  x_0 = x0;
  y_0 = y0;
  degree = dir0;
  
  C = draw::BLACK;
  
  status = true;
}

void Turtle::turn(double deg) {
  degree = degree + deg;
}

void Turtle::move(double distance) {
  double x1 = x_0;
  double y1 = y_0;
  double x2 = x1 + (distance*cos((degree*M_PI)/180.0));
  double y2 = y1 + (distance*sin((degree*M_PI)/180.0));
  
  draw::setcolor(C);
  
  if (status == true) {
    draw::line(x1, y1, x2, y2);
  }
  
  x_0 = x2;
  y_0 = y2;
}

void Turtle::setColor (Color c) {
  C=c;
}

void Turtle::off() {
  status = false;
}

void Turtle::on() {
  status = true;
}
