// Paul Kim, pbkim@usc.edu
// Homework 4 Code (RSA Encryption/Decryption)

// Including Useful Libraries
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <math.h>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// Can use in CPP files (Piazza)
using namespace std;

// Function Prototypes
long ModularExponentiation(long base, int exponent, int mod);   // Prototype for Modular Exponentiation Function
void StringtoInt(string message, queue<string>& queue, int n);  // Protoype for StringtoInt Function
int Euclidean(int a, int b);                                    // Prototype for GCD Function
int extendedEuclidean(int e, int L);                            // Prototype for Extended GCD Function
string LongtoString(long M, int x);  // Prototype for Function that converts a long value back into a string

// Main Program
int main(int argc, char* argv[]) {
    queue<string> OriginalIntString;  // Queue declared used to hold string in integer form

    if (argc != 3) {  // Error checking, checking for three arguments, including ./Program (3 total)
        throw exception();
    }

    // Using two Command-Line Parameters
    // Assuming here that p and q are large primes (Prompt) // No checking required
    // If not prime, algorithm should still run and not crash.
    int p = stoi(argv[1]);
    int q = stoi(argv[2]);
    const int e = 65537;    // Prompt (common choice of e)
    int PublicKey = p * q;  // Public Key shared (we do not have to check if prime)

    // Calculating LCM using formula from Prompt
    int LeastCommonMultiple = ((p - 1) * (q - 1)) / Euclidean(p - 1, q - 1);
    if (LeastCommonMultiple <= e) {  // Condition needs to be met
        cout << "LCM less than e" << endl;
        exit(0);
    }

    // Error checking that needs to be met declared by Prompt
    int ErrorChecking = Euclidean(e, LeastCommonMultiple);
    if (ErrorChecking != 1) {
        cout << "Error, gracefully terminating" << endl;
        exit(0);
    }

    // Using extendedEuclidean algorithm to find the DecryptionKey
    int DecryptionKey = extendedEuclidean(e, LeastCommonMultiple);  // Finding d that satisfies d * e mod L = 1
    if (DecryptionKey < 0) {                                        // If DecryptionKey is Negative
        DecryptionKey = DecryptionKey + ((p - 1) * (q - 1));
    }

    // Main Loop that continually loops until and error or EXIT is called
    // PIAZZA @1419, all commands will be passed in ALL-CAPS
    string condition = "";
    while (condition != "EXIT") {
        cout << "Please enter a valid command, and valid following arguments" << endl;

        cin >> condition;  // User Input

        if (condition == "EXIT") {  // If user calls EXIT
            exit(0);                // Gracefully terminates program
        }

        // Decrypts the message and overwrites content to an output file
        else if (condition == "DECRYPT") {  // If user calls DECRYPT
            string filename;
            string outputfilename;
            string EncryptedString;
            string DecryptedString;

            cin >> filename;
            cin >> outputfilename;

            int x = 1
                    + (log10(PublicKey / 27)
                       / log10(100));  // Change of Base Log Formula (Used to Calculate # of characters)

            ifstream myfile(filename);         // Opening Input File
            ofstream outfile(outputfilename);  // Output File

            if (!myfile.is_open()) {  // Condition if File Cannot Open
                cout << "Cannot open, gracefully terminating" << endl;
                exit(0);
            }

            else {
                while (myfile >> EncryptedString) {  // Inputting each instance of word into string
                    long M = ModularExponentiation(
                            stol(EncryptedString),
                            DecryptionKey,
                            PublicKey);  // Calculating original key from EncryptedString
                    string temp2 = LongtoString(
                            M, x);     // Converting the long value into strings and their respective characters
                    outfile << temp2;  // Outputting string into a file
                }
                outfile.close();  // Closing file
            }
        }

        // Creates/overwrites the file at the path, writing an ecrpyed version of message.
        else if (condition == "ENCRYPT") {  // If user calls Encrypt
            string filename;
            string n;        // Check if n is passed in or computed above from p and q.
            string message;  // Passed a message string

            cin >> filename;
            cin >> n;
            cin >> ws;  // Used to remove leading white space

            getline(cin, message);  // Message is a string of lowercase letters a-z and spaces.

            int x = 1 + (log10(stoi(n) / 27) / log10(100));  // Change of Base Log Formula

            if (stoi(n) < 27) {  // Condition needs to be met, or program terminates
                cout << "Error, gracefully terminating" << endl;
                exit(0);
            }

            // Converts String Message into their integer value
            // Seperates N into chunks such that Msg Size < N, using a Queue FIFO Functionality
            StringtoInt(message, OriginalIntString, x);

            ofstream myfile;  // Input file
            myfile.open(filename);
            while (!OriginalIntString.empty()) {          // Encrypting String in digit form stored in a queue.
                string temp = OriginalIntString.front();  // Good run time using Queue

                while (temp.length() != x * 2) {  // Condition to add trailing zeros if size is not equal to x*2.
                    temp += "0";                  // Adds trailing 0's
                }

                long value = ModularExponentiation(
                        stoi(temp),
                        e,
                        stoi(n));  // Calculates Encrypted Message using the Modular Exponentiation Algorithm
                string temp2 = to_string(value);  // Converting long value into a string

                // Writing number to output file, seperated by a single whitespace
                myfile << temp2 << " ";
                OriginalIntString.pop();  // Pop from queue to get next string
            }
            myfile.close();  // Closing file
            // Finished, Entire Message should be decrypted and saved to output file
        }

        else {  // If user enters invalid command
            cout << "Invalid Command" << endl;
        }
    }
}

// String to Int Function that takes the message and converts into integer form
void StringtoInt(string message, queue<string>& queue, int x) {
    string temp = "";
    string zeros = "";
    int len = message.length();
    int letter;
    int count = 0;

    for (int i = 0; i < len; i++) {  // Changing characters into integer values
        if (message[i] == ' ') {
            letter = 0;
        } else {
            letter = int(message[i] - 96);
        }

        ostringstream oss;  // Formatting String
        oss << setw(2) << setfill('0') << letter;

        if (count != x) {  // Adding to temporary string until count equals X
            temp = temp + oss.str();
            count++;
        } else {               // Push string into vector (IF count is greater than X)
            queue.push(temp);  // Push the X amount of characters in Integers into queue
            count = 1;         // Reset count after x digits, but add one of that iteration
            temp = "";         // Reset String
            temp = temp + oss.str();
        }
    }
    queue.push(temp);  // Pushing String into Queue
}

// Function that converts the int/long back into a string
string LongtoString(long M, int x) {
    string temp = to_string(M);
    char temp1, temp2;
    string temp3;
    string output = "";
    string space = " ";
    int value;
    long len = temp.length();
    bool condition = false;

    if (len % 2 != 0) {  // If leading 0 is erased, and number is odd add a begginning "0"
        temp = "0" + temp;
        len++;
    }

    if (len % 2 == 0) {  // If Even
        for (int i = 0; i < len; i += 2) {
            temp1 = temp[i];
            temp2 = temp[i + 1];
            if (temp2 == '0' && temp1 == '0') {  // Detects Space
                condition = true;
            }
            temp3 = string(1, temp1) + temp2;
            value = stoi(temp3) + 96;  // Should be two digits
            char character = value;
            string s(1, character);
            if (condition == true) {  // If Space
                output += space;
                condition = false;
            } else {
                output += s;
            }
        }
        if (output.length() != x) {  // Error Checking
            while (output.length() != x) {
                output = " " + output;
            }
            return output;
        } else {
            return output;
        }
    } else {  // If Odd
        for (long i = 0; i < len; i += 2) {
            temp1 = temp[i];
            temp2 = temp[i + 1];
            if (temp2 == '0' && temp1 == '0') {  // Detects Space
                condition = true;
            }
            temp3 = string(1, temp1) + temp2;
            value = stoi(temp3) + 96;  // Should be two digits
            char character = value;
            string s(1, character);
            if (condition == true) {  // If Space
                output += space;
                condition = false;
            } else {
                output += s;
            }
        }
        temp1 = temp[len - 2];
        temp2 = temp[len - 1];
        if (temp2 == '0' && temp1 == '0') {
            condition = true;
        }
        temp3 = string(1, temp1) + temp2;
        value = stoi(temp3) + 96;  // Should be two digits
        char character = value;
        string s(1, character);
        if (condition == true) {
            output += space;
            condition = false;
        } else {
            output += s;
        }
        if (output.length() != x) {  // Error Checking
            while (output.length() != x) {
                output = " " + output;
            }
            return output;
        } else {
            return output;
        }
    }
    return 0;
}

// ModularExponentiation Function (Lecture Notes)
long ModularExponentiation(long base, int exponent, int mod) {  // Inputs will fit inside a long for simplicity (Prompt)
    int result = 1;                                             // Initializing Result
    base = base % mod;
    if (base == 0) {
        return 0;
    }
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        exponent = exponent / 2;  // Divide Exponent by half (reducing size of loop)
        base = (base * base) % mod;
    }
    return result;
}

// GCD Algorithm
int Euclidean(int a, int b) {
    int x = a;
    int y = b;
    int r = 0;
    while (y != 0) {
        r = x % y;
        x = y;
        y = r;
    }
    return x;
}

// We use the extended version to calculate D, while also computing GCD
int extendedEuclidean(int e, int L) {
    int s = 0, t = 1, r = e;  // Initializing Variables
    int olds = 1, oldt = 0, oldr = (e * 0) + (L * 1);
    int quotient, temp;
    while (r != 0) {
        quotient = oldr / r;  // Automatically Rounds Down since quotient is an integer
        temp = r;
        r = oldr - quotient * r;
        oldr = temp;
        temp = s;
        s = olds - quotient * s;
        olds = temp;
        temp = t;
        t = oldt - quotient * t;
        oldt = temp;
    }
    return oldt;  // Returns Decryption Key
}