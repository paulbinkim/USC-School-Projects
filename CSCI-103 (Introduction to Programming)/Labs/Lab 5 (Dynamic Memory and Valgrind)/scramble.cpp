// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

int main(int argc, char **argv) {
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;
  
  if (argc != 2) {
    cout << "Wrong number of command line arguments" << endl;
    return 0;
  }

  /* Add code to declare the wordBank array, read in each word
     and store it */
  ifstream ifile (argv[1]);
  
  if (ifile.fail()) {
    cout << "Could not open file, the program will now quit" << endl;
    return 1;
  }
  
  int numWords;
  ifile >> numWords;
 
  if (ifile.fail()) {
    cout << "Value is not an integer, the program will now quit" << endl;
    return 1;
  }
 
  char** wordBank = new char*[numWords];
  char buffer[41];
  
  for (int i = 0; i < numWords; i++) {
    ifile >> buffer;
    wordBank[i] = new char[strlen(buffer)+1];
    strcpy (wordBank[i], buffer);
  }
  
  ifile.close();
    
  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  char* Guess =  new char [targetLen+1];
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    
    /* Complete the next line of code */
    strcpy (Guess, guess);
    
    if (strcmp(Guess, wordBank[target]) == 0) {
      wordGuessed = true;
      break;
    }
    
    numTurns--;   // Every guess counts as a turn
  }
  
  if (wordGuessed == true) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  
  /* Free up any necessary memory */
    
  delete[] word;
  for(int i=0; i < numWords; i++){
    delete[] wordBank[i];
  }
  delete [] wordBank;
  delete[] Guess;
  
  return 0;
}

// Scramble the letters. See "Knuth shuffle".
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}

