#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  char mystring[80] = "ComputerScience";
  char yourstring[80];
  char* astring = NULL; //if you do not get a segfault as expected
                 //change this to char* astring=NULL;
  yourstring = mystring; // Saying take the starting address of mystring and make it the starting address of yourstring.
  strncpy(astring, mystring, 80);

  astring = mystring; // make a copy?
  strncpy(yourstring, mystring, 80); // make a copy?
  cout << astring << endl; // What is in the address.
  cout << yourstring << endl;

  mystring[0] = '*'; // which one actually made a copy?
  cout << astring << endl;
  cout << yourstring << endl;

  return 0;
}