// Paul Kim, pbkim@usc.edu
// Hailstone Sequence program in which I
// implement a simple algorithm
// and determine the length until the number
// hits 1.

#include <iostream>
#include <climits>

using namespace std;

int main () {
  int x;
  int length = 0;
  
  cout << "Enter a number: ";
  cin >> x; // User input.
  
  while (x != 1) { // Formula of a hailstone.
    if (x % 2 == 0) {
      x = x/2;
      cout << x << " ";
      length++;
    }
    else {
      x = (x*3) + 1;
      cout << x << " ";
      length++;
    }
  }
  cout << endl;
  
  cout << "Length: " << length << endl;
  
  return 0;
}