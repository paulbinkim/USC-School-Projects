/* Paul Kim, pbkim@usc.edu
 * Commas program in which I make an algorithm that 
 * inputs a comma between every 3 numbers. I use a function
 * as I think it was very helpful for the repetition
 * of steps.
 * /


/********************************************************
 * Description:
 *  Displays a 64-bit integer (long long) with
 *   commas for thousands, millions, billions, etc.
 *
 * ** ABSOLUTELY NO ARRAYS, NO `string`, NO `vector` **
 *  usage is allowed.
 *
 * Instead, you may only declare:
 *
 *    bool,
 *    int, or
 *    int64_t (long long)
 *
 *  The only library function allowed is pow(base, exp)
 *    defined in the <cmath> library.
 *
 ********************************************************/

#include <iostream>
#include <cmath>
using namespace std;

void commas (unsigned long long n);

int main()
{
  long long n;
  cout << "Enter an integer:" << endl;
  
  /*====================*/
  /* Start of your code */
  
  cin >> n;
  
  if (n < 0) { // if negative, this applies.
    cout << '-';
    n *= -1;
  }
 
  commas (n); // call to function.
  cout << endl;
  
  
  /* End of your code */
  /*==================*/
  
  return 0;
}

void commas (unsigned long long n) { // function that repeats for every divisibility by 1000. Very neat
  if (n < 1000) {
    cout << n;
  }
  else {
    int remainder = n % 1000;
    commas (n/1000); // Will keep calling itself until satisfied.
    if (remainder == 0) {
      cout << ',' << "000";
    }
    else if (remainder < 10) {
      cout << ',' << "00" << remainder;
    }
    else if (remainder < 100) {
      cout << ',' << '0' << remainder;
    }
    else {
      cout << ',' << remainder;
    }
  }
}