/* Author: Paul Kim
 * Program: color_conv
 * Description: Converts RGB -> CMYK color representation
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
  double red, green, blue;
  double cyan, magenta, yellow, black;
  
  double max1, white;
  cout << "Enter 3 integers (red, green, and blue), in that order:";
   // Enter your code here
  cin >> red >> green >> blue;
  
  max1 = max (red/255, green/255);
  white = max (max1, blue/255);
  
  cyan = (white-(red/255))/white;
  magenta = (white-(green/255))/white;
  yellow = (white-(blue/255))/white;
  black = 1 - white;
  
  cout << "cyan: " << cyan << endl;
  cout << "magenta: " << magenta << endl;
  cout << "yellow: " << yellow << endl;
  cout << "black: " << black << endl;
   
  return 0;
}