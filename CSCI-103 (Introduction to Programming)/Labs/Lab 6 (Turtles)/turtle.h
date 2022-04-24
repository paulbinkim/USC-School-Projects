//Define the Turtle class here.

#include "draw.h"

class Turtle {
  public:
    Turtle (double x0, double y0, double dir0);
    void move (double distance);
    void turn (double deg);
    void setColor (Color c);
    void off();
    void on();
  private:
    double degree;
    double x_0;
    double y_0;
    bool status;
    Color C;
};

