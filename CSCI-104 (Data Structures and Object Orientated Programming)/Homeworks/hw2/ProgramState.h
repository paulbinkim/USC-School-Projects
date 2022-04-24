// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include <cctype>
#include <iostream>
#include <map>
#include <stack>

class ProgramState {
public:
    ProgramState(int numLines);                       // numLines = # of total lines in project
    void InsertMap(std::string variable, int value);  // Adds to map
    void InsertStack(int value);
    int PopStack();
    int GetValue(std::string variable);
    void Add(std::string variable, std::string variable2);
    void Sub(std::string variable, std::string variable2);
    void Mult(std::string variable1, std::string variable2);
    void Div(std::string variable1, std::string variable2);
    void Print(std::string variable1);
    void PrintAll();
    int getCounter();
    std::string mathOperator();
    void setCounter(int counter);
    int getTotallines();

private:
    int m_numLines;                   // Total Line Numbers in a Program
    int programCounter;               // Specifies the line number we are at.
    std::map<std::string, int> map1;  // Creating a map
    std::stack<int> stack1;           // Creating a stack
};

#endif

// Completed