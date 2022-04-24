// game.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank... already done for us.
  const char* targetWord = wordBank[rand() % numWords];

  // More initialization code as needed
  char word[80];  // a blank array to use to build up the answer
                  // It should be initialized with *'s and then
                  //  change them to the actual letters when the 
                  //  user guesses the letter

  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  
  int sizeWord = strlen(targetWord); // Used function strlen() to find the amout of '*'s needed to iniialize.
  
  for (int i = 0; i < sizeWord; i++) { // Initializing array to '*'s
    word[i] = '*';
  }
  word [sizeWord] = '\0'; // ending last with a null character
  
  for (int z = numTurns; z > 0; z--) { // Main for loop that iterates for Z turns.
    cout << "Current word: ";
    for (int i = 0; i < sizeWord; i++) {
      cout << word[i];
    }
    cout << endl;
    cout << z << " remain...Enter a letter to guess:" << endl;
    
    cin >> guess;
    
    int success = processGuess (word, targetWord, guess);
    if (success == 1) { // If word was guessed, the numTurns does not decrement.
      z++;
    } // Simply, if process = 1, else
    
    int result = strcmp (word, targetWord); // Always checks if the strings match.
    if (result == 0) { // If matched, exits for loop.
      wordGuessed = true;
      break;
    }
  } // Limit number of lines , less computation power. and More comments

  // Print out end of game status
  
  if (wordGuessed == false) {
    cout << "Too many turns...You lose!" << endl;
  }
  else {
    cout << "The word was: " << targetWord << ". You win!" << endl;
  }
  
  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
  int size = strlen(targetWord);
  bool exists = false;

  for (int i = 0; i < size; i++) {
    if (guess == targetWord[i]) { // Searches for char match. 
      word[i] = guess;
      exists = true;
    }
    word++; // Iterates the pointer.
    targetWord++;
  }
  
  if (exists == true) { // If word was found.
    return 1;
  }
  else { // If word was not found.
    return 0;
  }
  
}