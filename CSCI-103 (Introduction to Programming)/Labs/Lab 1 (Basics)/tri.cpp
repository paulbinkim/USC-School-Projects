#include <iostream>
#include <cmath>

using namespace std;

int main () {
  int height = 31;
  int angle;
  double ratio;
  
  cout << "Enter the angle theta in degrees:" << endl;
  cin >> angle;
  
  ratio = (tan(angle * (M_PI/180))); // convert into a factor of radians and find the Tan ratio.
                
  for (int i = 0; i < height; i++){ // iteration of rows.
    double drawing = floor(i*ratio); // money part (skips to for i = 0 and 1) function/ratio that tells how much stars to print.
    
    for (int z = 1; z <= drawing; z++) { // iteration of amount of starts(drawing) printed for each row.
      if (drawing >= 20 && drawing <= 30) { // function that cuts out block from rows 20 to 30
        for (int j = 1; j <= 20; j++) { // prints 20 as suggested.
          cout << "*";
        }
        break;
      }
      else {
        cout << "*";
      }
    }       
    cout << endl;
  }
  
  return 0;
}