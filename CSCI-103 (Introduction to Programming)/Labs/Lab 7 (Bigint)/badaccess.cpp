#include "bigint.h"
#include <iostream>
using namespace std;

int main() {
  
  BigInt a("5102");
  cout << a.digitbank.size() << endl; // This is an error, "___ is private within this context"
}

