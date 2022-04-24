// GotoStatements.cpp:
#include "GotoStatement.h"
using namespace std;  // (PIAZZA says can use)

GotoStatement::GotoStatement(int line)
        : linenum(line)  // Constructor
{}

void GotoStatement::execute(ProgramState* state, std::ostream& outf) {
    if (linenum > state->getTotallines() || linenum < 0) {
        cout << "Illegal jump instruction" << endl;  // (PIAZZA @797)
        exit(EXIT_FAILURE);
    }

    state->setCounter(linenum);  // Set programCounter to new line number
}

// Completed