// Paul Kim, pbkim@usc.edu
// permutations.cpp

// Useful libraries not included in STL
#include <iostream>  // cout functions
#include <string>    // .substr and .at functions

// Helper function that uses recursion and a for loop to print remaining characters.
void helper(std::string start, std::string end) {
    if (end.length() == 1) {                    // Base case (Recursion ends here)
        std::cout << start + end << std::endl;  // Concatenates beggining and end of string
    } 
    else if (start.length() == 1 && end.length() == 0) {
        std:: cout << start << std::endl; // Forgot this edge case***
    }
    
    else {
        for (unsigned int i = 0; i < end.length();
             i++) {  // Using unsigned int because valgrind displays an error (fixed it)
            helper(start + end.at(i), end.substr(0, i) + end.substr(i + 1));  // (Recursive call here)
        }
    }
}
// Main function that iterates through length of string, and makes a call on helper.
void permutations(std::string in) {
    for (unsigned int i = 0; i < in.length(); i++) {
        helper(in.substr(i, 1), in.substr(0, i) + in.substr(i + 1));  // Call to helper function that does all work.
    }
}

// No memory leaks