// EndStatement.cpp:
#include "EndStatement.h"
using namespace std;  // (PIAZZA says can use)

EndStatement::EndStatement() {}  // Constructor

void EndStatement::execute(ProgramState* state, std::ostream& outf) {
    state->setCounter(0);  // If End or . is called, set the programCounter to 0.
}

// Completed