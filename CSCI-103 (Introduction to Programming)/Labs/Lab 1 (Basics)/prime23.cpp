#include <iostream>

using namespace std;

int main () {
  int x;
  int twocount = 0;
  int threecount = 0;
  bool Prime = true;
 
  cout << "Enter a positive integer:" << endl;
  cin >> x;
  
  if (x == 1 || x == 0) {
    cout << "No" << endl;
    return 0;
  }
  
  while (x % 2 == 0 || x % 3 == 0) {
    if (x % 2 == 0) {
      twocount++;
      x = x/2;
    }
    else if (x % 3 == 0) {
      threecount++;
      x = x/3;
    }
  }
  
  if (x != 1){
      Prime = false;
  }

  if (Prime == true) {
    cout << "Yes" << endl;
    cout << "Twos=" << twocount << " Threes=" << threecount << endl;
  }
  else {
    cout << "No" << endl;
  }

  return 0;
}