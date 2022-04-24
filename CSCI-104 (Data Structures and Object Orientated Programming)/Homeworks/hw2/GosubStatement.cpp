// GosubStatement.cpp:
#include "GosubStatement.h"
using namespace std;  // (PIAZZA says can use)

GosubStatement::GosubStatement(int line)
        : linenum(line)  // Constructor
{}

void GosubStatement::execute(ProgramState* state, std::ostream& outf) {
    if (linenum > state->getTotallines() || linenum < 0) {
        cout << "Illegal jump instruction" << endl;  // (PIAZZA @797)
        exit(EXIT_FAILURE);
    }
    int currentline = state->getCounter();  // Gets current counter of programline.
    state->InsertStack(currentline + 1);    // Insert currentline into stack.
    state->setCounter(linenum);             // Set currentcounter to new line number declared by GOSUB
}

// Completed