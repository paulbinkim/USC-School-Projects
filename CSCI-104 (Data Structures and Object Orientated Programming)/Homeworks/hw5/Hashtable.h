// Including Useful Libraries for Functionality
#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <random>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>

// Pre-defined R values
#define r1 983132572
#define r2 1468777056
#define r3 552714139
#define r4 984953261
#define r5 261934300

// Templated Class
template<typename T>
class Hashtable {
public:
    Hashtable(bool debug = false, unsigned int size = 11);  // Default Argument
    ~Hashtable();
    int add(std::string k, const T& val);
    const T& lookup(std::string k);
    void reportALL(std::ostream&) const;

protected:
    int hash(std::string k) const;

private:
    void resize();
    void insert(std::string k);
    unsigned int tablesizes[28] // Pre-determined table sizes
            = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
    int tablesizeIndex;
    unsigned int currentsize;
    double loadfactor;
    int numData;
    bool debug;
    T garbage;
    long long r[5];
    std::vector<std::pair<std::string, int>*> table; // Table used to store values
};

// Constructor
template<typename T>
Hashtable<T>::Hashtable(bool debug, unsigned int size) {
    this->currentsize = size;
    this->loadfactor = 0;
    this->numData = 0;

    // Finds size and location of the size of the table array
    if (size == 11) {
        tablesizeIndex = 0;
    } else {
        int tempcounter = 0;
        for (int i = 0; i < 28; i++) {
            if (size > tablesizes[i]) {
                tempcounter++;
            }
            else {
                break;
            }
        }
        tablesizeIndex = tempcounter-2;
    }
    
    // Initializes the size of the table
    for (unsigned int i = 0; i < currentsize; i++) {
        table.push_back(NULL);
    }
    
    // Debug Conditions
    if (debug == true) {
        this->debug = true;
        // do true condition
        this->r[0] = r1;
        this->r[1] = r2;
        this->r[2] = r3;
        this->r[3] = r4;
        this->r[4] = r5;
    } else {
        this->debug = false;
        // do false condition
        this->r[0] = rand() % currentsize;
        this->r[1] = rand() % currentsize;
        this->r[2] = rand() % currentsize;
        this->r[3] = rand() % currentsize;
        this->r[4] = rand() % currentsize;
    }
}

// Deconstructor (no memory leaks)
template<typename T>
Hashtable<T>::~Hashtable() {
    for (unsigned int i = 0; i < currentsize; i++) {
        delete table[i];
    }
}

// If k is already in hash table then do nothing. If new, add to the hash table.
// Returns # of probes required to place k.
template<typename T>
int Hashtable<T>::add(std::string k, const T& val) {
    int probes = 0;
    // first check if already in the hash table
    if (lookup(k) != garbage) {  // meaning that string does not exist in table
        return 0;             
    }

    if (loadfactor >= 0.5) {
        resize();
    }
    numData++;
    loadfactor = (double)numData / (double)currentsize;

    int hash1 = hash(k);

    int i = 0;
    if (table[hash1] != NULL) {  // If hash index is taken, will enter
        probes++;
        i++;
        hash1 = (hash1 + (i * i)) % this->currentsize;
        while (table[hash1] != NULL) {
            i++;
            probes++;
            hash1 = (hash1 + (i * i)) % this->currentsize;
        }
        table[hash1] = new std::pair<std::string, int>(k, val);
        return probes;
    } else { // Else, just enter
        table[hash1] = new std::pair<std::string, int>(k, val);
        return probes;
    }
}

// Helper function that doubles the number of indices available, if load factor increases above 0.5
template<typename T>
void Hashtable<T>::resize() {
    int oldsize = currentsize;
    tablesizeIndex++;  // We want to go to the next table size in the array pre-determined array
    currentsize = tablesizes[tablesizeIndex];

    // Create a new hashtable
    std::vector<std::pair<std::string, int>*> oldTable = table;
    std::vector<std::pair<std::string, int>*> newTable;

    for (unsigned int i = 0; i < currentsize; i++) {  // Make a new table
        newTable.push_back(NULL);
    }

    table = newTable;  // now table is an empty table with bigger size
    
    // We rehash in order from beggining to end
    for (int j = 0; j < oldsize; j++) {
        if (oldTable[j] != NULL) {
            add(oldTable[j]->first, oldTable[j]->second);
        }
    }
}

// Lookup function that returns the value of the string, or garbage
template<typename T>
const T& Hashtable<T>::lookup(std::string k) {
    int hash1 = hash(k);
    int i = 0;
    while (table[hash1]) {
        if (table[hash1]->first == k) {
            return table[hash1]->second;
        } else {
            i++;
            hash1 = (hash1 + (i * i)) % this->currentsize; 
        }
    }
    return garbage;  // garbage value, if doesn't exist
}

// Output every pair in the order they appear in the hash table.
template<typename T>
void Hashtable<T>::reportALL(std::ostream& output) const {
    for (unsigned int i = 0; i < this->currentsize; i++) {
        if (table[i] != NULL) {
            output << table[i]->first << " " << table[i]->second << std::endl;
        }
    }
}

// Takes a string as input, and outputs a pseudo-random index to store it.
// Never passed in a string greater than 28 characters
// Use long long for everything
template<typename T>
int Hashtable<T>::hash(std::string k) const {
    // First, translating each letter into a value between 1 and 26. (a = 1, b = 2...)
    int stringIndex = k.length() - 1;  // Captures last index of string
    long long temparray[4];            // Used to hold w1,w2,w3,w4,w5 (use long long)
    long long letter;
    for (int i = 4; i >= 0; i--) {  // Start from end to front.
        long long temp = 0;
        for (int j = 0; j < 6; j++) {
            if (stringIndex != -1) {
                letter = long(k[stringIndex] - 96);  // only passed lowercase characters (only one long)
                temp = temp + ((long long)pow(27, j)) * letter;
                stringIndex--;
            }
        }

        temparray[i] = temp;  // Will store values if changed, else, will just store a 0
    }

    long long sum = 0;

    // Multiplying r(i)*w(i) as shown in formula
    for (int i = 0; i < 5; i++) {
        long long tempvalue = (long long)r[i] * (long long)temparray[i];
        sum += (long long)tempvalue;
    }
    long long hash = sum % (long long)currentsize;  // Returns hash
    return hash;
}