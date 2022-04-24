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
    double probe = 0;
    srand(time(NULL));
    Hashtable<int> hashtable(true, 11);

    for (int i = 0; i < 10; i++) {  // Run arbitraility times (10000)
        
        // Code that generates a random string
        string word = "";
        int length = (rand() % 50) + 1;
        for (int t = 0; t < length; t++) {
            word += 'a' + (rand() % 26);
        }

        probe += hashtable.add(word, 1);
        cout << probe << endl;
    }
    double percentage = probe / 10000;  // Finds percentage
    cout << percentage << endl;
    hashtable.reportALL(cout);
    // End of Birthday Paradox Code

    return 0;
}