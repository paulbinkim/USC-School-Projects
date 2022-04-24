#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

// sum an array of numbers
int test1(int *data, int len)
{
  int sum = 0;
  for(int i=0; i < len; i++){ // Bug, was accessing data[6] which did not exist <= -> <
    sum += data[i];
  }
  return sum;
}

// Allocate a random number array
char* test2_init(int len)
{
  char buf[80];
  cout << "Enter a word: ";
  cin >> buf;
  char* mydat = new char[strlen(buf)+1];
  strcpy(mydat, buf);
  return mydat;
}

char* test2_reverse(char* word)
{
  int len = strlen(word);
  char* otherword = new char[len+1];
  
  for(int i=0; i < len; i++){ // Changed strlen(word) -> len
    otherword[i] = word[len-i-1];
  }
  otherword[len] = '\0'; // Out of array error bug, fixed.
  return otherword;
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please enter the test number you want to run [1-2]" << endl;
    return 1;
  }
  const int len = 7;
  int test = atoi(argv[1]);

  if(test == 1){
    // Test should sum up the array values and print it
    int *data = new int[len];
    
    for(int i=0; i < len; i++){
      data[i] = rand()%100;
    }
    
    int sum = test1(data, len);
    cout << "Test 1 sum is " << sum << endl;
    
    delete[] data; // Deallocated memory used for line 50 (First step, test 1)
  }

  else if(test == 2){
    // Test should create a random string & then reverse a copy
    char* myword = test2_init(len);
    cout << "myword is " << myword << endl;
 
    char* otherword = test2_reverse(myword);    
    cout << "otherword is " << otherword << endl;
   
    delete [] myword; // Bug Fix (Was a different variable name)
    delete [] otherword;
  }
  else {
    cout << "Unknown test number" << endl;
  }

  return 0;
}
