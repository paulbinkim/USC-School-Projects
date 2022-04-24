#include <iostream>

using namespace std;

int main() {
  int x;
  
  cout << "Enter an integer between 0 and 999:" << endl;
  cin >> x;
  
  cout << "1's digit is " << (x % 10) << endl;
  x /= 10;
  cout << "10's digit is " << (x % 10) << endl;
  x /= 10;
  cout << "100's digit is: " << (x % 10) << endl;
  
  return 0;
}