// Paul Kim, pbkim@usc.edu
// Searching Hailstones program in which
// I build upon the same algorithm from
// the last assignment, but this time
// keep track of a number within a range
// and output the most minimum and max 
// length.


#include <iostream>

using namespace std;

int main () {
  int lower, upper; // Declaring all variables needed.
  int length = 0;
  int maxlen = 0;
  int minlen = 99;
  int minlenName, maxlenName;
  bool oneexist = false; // Extra because there was a flaw in my design.
  
  cout << "Enter the range that you want to search: ";
  cin >> lower >> upper; // User input.
  
  if (upper < lower) { // If bounds error.
    cout << "Invalid range" << endl;
    return 0;
  } 
  
  for (int i = lower; i <= upper; i++) { // Loop that interates for the entire range for the hailstone.
    lower = i;
    while (lower != 1) {
      if (lower % 2 == 0) {
        lower = lower/2;
        length++;
        }
      else {
        lower = (lower*3) + 1;
        length++;
      }
    }
    if (i == 1) { // Special case I added
      oneexist = true;
    }
    if (maxlen == 0) { // From here below, I replace variables if conditions are satisfied.
      maxlen = length;
      maxlenName = i;
      minlen = length;
      minlenName = i;
    }
    else if (length < minlen) {
      minlen = length;
      minlenName = i;
    }
    else if (length > maxlen) {
      maxlen = length;
      maxlenName = i;
    }
    length = 0;
  }
  
  if (oneexist == true) { // Extra that replaces the min if the range went through 1.
    minlen = 0;
    minlenName = 1;
  }
  
  cout << "Minimum length: " << minlen << endl;
  cout << "Achieved by: " << minlenName << endl;
  cout << "Maximum length: " << maxlen << endl;
  cout << "Achieved by: " << maxlenName << endl;
  
  return 0;
}