// I want to add all my implementation details here.
// ProgramState.cpp:
#include "ProgramState.h"

#include <cmath>
using namespace std;

ProgramState::ProgramState(int numLines)  // Main Constructor
        : m_numLines(numLines), programCounter(1) {}

void ProgramState::InsertMap(std::string variable, int value) {  // Inserts variable and value into a map (STL)
    if (map1.find(variable) == map1.end()) {                     // Goes through entire map without finding duplicate
        map1.insert(make_pair(variable, value));
    } else {
        map1.find(variable)->second = value;  // Used for let function to update variable
    }
}

int ProgramState::PopStack() {  // Pop Stack
    if (stack1.empty()) {
        exit(EXIT_FAILURE);
    }
    int value = stack1.top();
    stack1.pop();
    return value;
}

int ProgramState::GetValue(std::string variable) {  // Get Value from variable using a map
    if (map1.find(variable) == map1.end()) {
        return 0;
    } else {
        int value = map1.find(variable)->second;
        return value;
    }
}

int ProgramState::getTotallines() { return this->m_numLines; }

void ProgramState::InsertStack(int value) {  // Insert Stack
    stack1.push(value);
}

void ProgramState::setCounter(int counter) {  // Set a counter to a line number
    this->programCounter = counter;
}

int ProgramState::getCounter() {  // Get current counter
    return programCounter;
}

void ProgramState::Add(std::string variable, std::string variable2) {  // Add functionality
    if (isdigit(variable2[0])) {
        int value2 = stoi(variable2);
        // CHECKING IF VARIABLE1 EXISTS
        if (map1.find(variable) == map1.end()) {  // Variable doesn't exist, so you would just initialize to the value
            map1.insert(make_pair(variable, value2));  // Initial value is 0 so just add value2
        } else {
            map1.find(variable)->second += value2;  // Multiply to the 2nd parameter of the map
        }
    } else if (variable2[0] == '-') {  // Here we know that variable two is a digit. (Variable name cannot start with
                                       // "-").
        int value2 = stoi(variable2);
        map1.find(variable)->second += value2;
    }

    else {
        if (map1.find(variable2) == map1.end()) {  // Variable doesn't exist, so you would just initialize to the value
            map1.insert(make_pair(variable2, 0));  // Initial value is 0 so just add value2
        }
        int var2val = map1.find(variable2)->second;
        map1.find(variable)->second += var2val;  // Adds to the 2nd parameter of the map
    }
}

void ProgramState::Sub(std::string variable, std::string variable2) {
    if (isdigit(variable2[0])) {
        int value2 = stoi(variable2);
        // CHECK IF VARIABLE1 EXISTS
        if (map1.find(variable) == map1.end()) {  // Variable doesn't exist, so you would just initialize to the value
            map1.insert(make_pair(variable, value2));  // Anything subtracted by 0 stays the same
        } else {
            map1.find(variable)->second -= value2;  // Multiply to the 2nd parameter of the map
        }
    } else if (variable2[0] == '-') {  // Here we know that variable two is a digit. (Variable name cannot start with
                                       // "-").
        int value2 = stoi(variable2);
        map1.find(variable)->second -= value2;
    }

    else {
        if (map1.find(variable2) == map1.end()) {  // Variable doesn't exist, so you would just initialize to the value
            map1.insert(make_pair(variable2, 0));  // Initial value is 0 so just add value2
        }
        int var2val = map1.find(variable2)->second;
        map1.find(variable)->second -= var2val;  // Adds to the 2nd parameter of the map
    }
}

void ProgramState::Mult(std::string variable1, std::string variable2) {
    if (map1.find(variable1) == map1.end()) {
        map1.insert(make_pair(variable1, 0));  // ERROR CHECKING IF VARIABLE 1 DOESN'T EXIST (CANNOT FIND)
    }

    if (isdigit(variable2[0])) {
        int value2 = stoi(variable2);
        map1.find(variable1)->second *= value2;  // Multiply to the 2nd parameter of the map
    } else if (variable2[0] == '-') {  // Here we know that variable two is a digit. (Variable name cannot start with
                                       // "-").
        int value2 = stoi(variable2);
        map1.find(variable1)->second *= value2;
    } else if (map1.find(variable2) == map1.end()) {  // We know by error checking, that variable2 must be a variable
        map1.insert(make_pair(variable2, 0));         // ERROR CHECKING IF VARIABLE 2 DOESN'T EXIST
        map1.find(variable1)->second *= 0;  // Says that variable 2 didn't exist, so now multiplying by initialized 0
    }

    else {  // When variable 2 exists
        int value2 = map1.find(variable2)->second;
        map1.find(variable1)->second *= value2;  // Multiply to the 2nd parameter of the map
    }
}

void ProgramState::Div(std::string variable1, std::string variable2) {
    if (map1.find(variable1) == map1.end()) {
        map1.insert(make_pair(variable1, 0));  // ERROR CHECKING IF VARIABLE 1 DOESN'T EXIST
    }
    if (isdigit(variable2[0])) {  // if variable 2 is an digit
        int value2 = stoi(variable2);
        if (value2 == 0) {
            cout << "Divide by zero exception." << endl;  // Divide by 0
            exit(EXIT_FAILURE);
        } else {
            map1.find(variable1)->second /= value2;  // Multiply to the 2nd parameter of the map
        }
    } else if (variable2[0] == '-') {     // Here we know that variable two is a digit. (Variable name cannot start with
                                          // "-").
        double value2 = stoi(variable2);  // DIVISION FLOOR
        double value3 = map1.find(variable1)->second;
        map1.find(variable1)->second = floor(value3 / value2);
    }

    else if (map1.find(variable2) == map1.end()) {    // When variable 2 is a variable, and cannot find.
        map1.insert(make_pair(variable2, 0));         // ERROR CHECKING IF VARIABLE 2 DOESN'T EXIST
        cout << "Divide by zero exception." << endl;  // Divide by 0
        exit(EXIT_FAILURE);
    }

    else {
        int value2 = map1.find(variable2)->second;
        if (value2 == 0) {
            cout << "Divide by zero exception." << endl;  // Divide by 0
            return;
        } else {
            map1.find(variable1)->second /= value2;  // Multiply to the 2nd parameter of the map
        }
    }
}

void ProgramState::Print(std::string variable1) {
    if (map1.find(variable1) == map1.end()) {
        map1.insert(make_pair(variable1, 0));  // Initialize
        cout << "0" << endl;                   // When variable doesn't exist
    } else {
        int value = map1.find(variable1)->second;
        cout << value << endl;  // Outputs value corresponding to entered variable
    }
}

void ProgramState::PrintAll() {
    std::map<std::string, int>::iterator it = map1.begin();
    while (it != map1.end()) {  // Maps automatically store values in sort order
        cout << it->first << " " << it->second << endl;
        it++;
    }
}
