#include "Hashtable.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

int main() {
    // Start of Birthday Paradox Code
    // Initializing Variables
    double numofItems = 0;
    double success = 0;
    int probe;
    srand(time(NULL));

    for (int i = 0; i < 10000; i++) {  // Run arbitraility times (10000)
        Hashtable<int> hashtable(true, 365);
        // Code that generates a random string
        string word = "";
        int length = (rand() % 500) + 1;
        for (int t = 0; t < length; t++) {
            word += 'a' + (rand() % 26);
        }

        probe = hashtable.add(word, 1);
        numofItems++;

        while (probe == 0) {
            string word = "";
            int length = (rand() % 500) + 1;
            for (int t = 0; t < length; t++) {
                word += 'a' + (rand() % 26);
            }
            probe = hashtable.add(word, 1);
            numofItems++;
        }
        // If numofItems is less than 23, then birthday paradox proves true
        if (numofItems <= 23) {
            success++;
        }

        numofItems = 0;
    }
    double percentage = success / 10000;  // Finds percentage
    cout << percentage << endl;
    // End of Birthday Paradox Code

    return 0;
}