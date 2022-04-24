// Program that reads in a valid program from an input stream.
// Interpreter.cpp
#include "EndStatement.h"
#include "GosubStatement.h"
#include "GotoStatement.h"
#include "If.h"
#include "LetStatement.h"
#include "MathOperators.h"
#include "PrintAllstatement.h"
#include "PrintStatement.h"
#include "ProgramState.h"
#include "Return.h"
#include "Statement.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;  // PIAZZA POST SAID THIS IS ALLOWED (and already pre-included)

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement*>& program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement* parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

// Main
int main() {
    cout << "Enter BASIC program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }
    interpretProgram(infile, cout);
}

// Called in main that re-runs that calls "parseline"
void parseProgram(istream& inf, vector<Statement*>& program) {
    program.push_back(NULL);

    string line;
    while (!inf.eof()) {
        getline(inf, line);
        program.push_back(parseLine(line));
    }
}

// Parseline function that executes conditions depending on type
Statement* parseLine(string line) {
    Statement* statement = nullptr;
    stringstream ss;
    string type;
    string var;
    string var2;         // Added
    string op;           // Added
    string emptystring;  // Added
    int val;
    int condition;   // Added
    int linenumber;  // Added

    ss << line;
    ss >> linenumber;  // Useless but needed
    ss >> type;

    if (type == "LET")  // Let Statement
    {
        ss >> var;
        ss >> val;
        statement = new LetStatement(var, val);
    } else if (type == "END" || type == ".") {  // Combine Period and End (Same Function) (End/Period Statement)
        statement = new EndStatement();
    } else if (type == "ADD") {  // Add Statement
        ss >> var;
        ss >> var2;
        statement = new MathOperators(var, var2, "ADD");
    } else if (type == "SUB") {  // Subtract Statement
        ss >> var;
        ss >> var2;
        statement = new MathOperators(var, var2, "SUB");
    } else if (type == "DIV") {  // Division Statement
        ss >> var;
        ss >> var2;
        statement = new MathOperators(var, var2, "DIV");
    } else if (type == "MULT") {  // Multiply Statement
        ss >> var;
        ss >> var2;
        statement = new MathOperators(var, var2, "MULT");
    } else if (type == "PRINT") {  // Print Statement
        ss >> var;
        statement = new PrintStatement(var);
    } else if (type == "PRINTALL") {  // Printall Statement
        statement = new PrintAllstatement();
    } else if (type == "GOTO") {  // Goto Statement
        ss >> val;
        statement = new GotoStatement(val);
    } else if (type == "GOSUB") {  // GoSub Statement
        ss >> val;
        statement = new GosubStatement(val);
    } else if (type == "RETURN") {  // Return Statement
        statement = new Return();
    } else if (type == "IF") {  // If Statement
        ss >> var;
        ss >> op;
        ss >> condition;
        ss >> emptystring;  // "THEN" (Completely Useless but have to pass in input)
        ss >> val;
        statement = new If(var, op, condition, val);
    }

    return statement;
}

void interpretProgram(istream& inf, ostream& outf) {
    vector<Statement*> program;
    parseProgram(inf, program);
    ProgramState* ProgramState1 = new ProgramState(program.size());

    while (program[ProgramState1->getCounter()] != NULL) {  // Main Loop that executes functions
        int counter = ProgramState1->getCounter();
        program[counter]->execute(ProgramState1, outf);
    }

    // Deallocating Dynamic Memory
    for (long unsigned int i = 1; i < program.size(); i++) {
        delete program[i];
    }
    delete ProgramState1;
}

// Completed