/* Paul Kim, pbkim@usc.edu
 * Twenty-One program in which I create the
 * game Blackjack using numerous functions.
 */

// #Includes and functions.
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

// Pre-declared variables.
const int NUM_CARDS = 52;
const char suit[4] = {'H','S','D','C'}; 
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

void shuffle(int cards[]) // Shuffle Function that shuffles the initialized cards.
{
  for (int i = NUM_CARDS-1; i > 0; i--) {
    int j = rand() % (i+1);
    swap(cards[j], cards[i]);
  }
}

void printCard(int id) { // Transforms Integer to Type-Suit Card.
  int remainder = 0;
  if (id == 0) {
      cout << type[0] << '-' << suit[0];
  }
  else if (id <= 12) { // H
    remainder = id % 13;
    cout << type[remainder] << '-' << suit[0];
  }
  
  else if (id <= 25) { // S
    remainder = id % 13;
    cout << type[remainder] << '-' << suit[1];
  }
  
  else if (id <= 38) { // D 
    remainder = id % 13;
    cout << type[remainder] << '-' << suit[2];
  }
  
  else if (id <= 51) { // C
    remainder = id % 13;
    cout << type[remainder] << '-' << suit[3];
  }
}

int cardValue(int id) { // Returns Numeric Value of the Card
  int remainder = 0;
  remainder = id % 13;
  if (id == 0) {
    return 2;
  }
  else if (remainder <= 7) {
    int value = remainder + 2;
    return value;
  }
  else if (remainder <= 11) {
    return 10;
  }
  else if (remainder == 12) {
    return 11;
  }
  return 0;
}

void printHand(int hand[], int numCards) { // Prints out the hand of either the dealer or player.
  for (int i = 0; i < numCards; i++) {
    int value = hand[i];
    printCard(value);
    cout << " ";
  }
  cout << endl;
}

int getBestScore(int hand[], int numCards) { // Returns the total score of the hand.
  int sum = 0;
  int numAces=0;
  for (int i = 0; i < numCards; i++) {
    int value = cardValue (hand[i]);
    sum+=value;
    if (value == 11) {
      numAces++;
    }
    if (sum > 21 && numAces > 0) {
        sum = sum - 10;
        numAces--;
    }
  }
  return sum;
}

/**
 * Main program logic for the game of 21
 */

int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  int pcount = 0; // Implementing more variables that I will use.
  int dcount = 0;
  int twentyone = 0;
  bool loser = false;
  char HitorStand = 'h';
  char playagain = 'y';

  while (playagain == 'y') { // Repeating loop for numerous games.
    for (int i = 0; i < 52; i++) { // Initializing deck(s) to have values 0-51
      cards[i] = i;
    }
    for (int i = 0; i < 9; i++) {
      dhand[i] = 0;
    }
    for (int i = 0; i < 9; i++) {
      phand[i] = 0;
    }
  
    shuffle (cards); // Shuffle Function
      
    for (int i = 0; i < 2; i++) { // Initializing starting Dealer's Hand
      dhand[i] = cards[i+1+i];
      dcount++;
    }
    for (int i = 0; i < 2; i++) { // Initializing starting Player's Hand
      phand[i] = cards[i+i];
      pcount++;
    }
  
    cout << "Dealer: " << "? "; // Initial output statement.
    printCard(dhand[1]);
    cout << endl << "Player: ";
    printHand(phand, pcount);
  
    twentyone = getBestScore (phand, pcount);
  
    if (twentyone == 21) {
      HitorStand = 's';
    }
  
    int cardPos = 4;
  
    while (HitorStand != 's') { // Loop that continues to draw card(hit) until user enters 's'
      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin >> HitorStand;
   	  if (HitorStand == 'h') {
      	phand[pcount] = cards[cardPos];
      	pcount++;
      	cardPos++;
      	cout << "Player: ";
      	printHand(phand, pcount);
      	twentyone = getBestScore (phand, pcount);
      	if (twentyone > 21) {
        	cout << "Player busts" << endl;
        	cout << "Lose " << twentyone << ' ' << getBestScore(dhand, dcount) << endl;
        	loser = true;
        	break;
      	}
      	else if (twentyone == 21) {
        	break;
      	}
   	  }
      else {
      	break;
      }
  	}
    
    if (loser == false) { // Dealers turn main code.
    	int value = getBestScore(dhand, dcount);
    	while (value < 17) {
       		dhand[dcount] = cards[cardPos];
       		dcount++;
       		cardPos++;
       		value = getBestScore(dhand,dcount);
    	}
    	cout << "Dealer: ";
    	printHand(dhand, dcount);
    	int valueplayer = getBestScore(phand,pcount);
    	int valuedealer = getBestScore(dhand,dcount);
    	if (value <= 21) {
      		if (valuedealer > valueplayer) {
        		loser = true;
        		cout << "Lose " << valueplayer << ' ' << valuedealer << endl;
      		}
      		else if (valuedealer == valueplayer) {
        		loser = true;
        		cout << "Tie " << valuedealer << ' ' << valuedealer << endl;
      		}
          else if (valueplayer > valuedealer) {
            loser = true;
            cout << "Win " << valueplayer << ' ' << valuedealer << endl;
          }
    	}
    	else {
      		loser = true;
      		cout << "Dealer busts" << endl;
      		cout << "Win " << twentyone << ' ' << valuedealer << endl;
    	}
    }
    dcount = 0; // Resets everything for the next iteration for the game.
    pcount = 0;
    loser = false;
    HitorStand = 'h';

    cout << endl;
    cout << "Play again? [y/n]" << endl;
    cin >> playagain;
  }
  return 0; 
 }