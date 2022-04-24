// PrintAllstatement.cpp:
#include "PrintAllstatement.h"
using namespace std;  // (PIAZZA says can use)

PrintAllstatement::PrintAllstatement() {}  // Constructor

void PrintAllstatement::execute(ProgramState* state, std::ostream& outf) {
    state->PrintAll();  // Calls PrintAll function declared in ProgramState
    int counter = state->getCounter();
    state->setCounter(counter + 1);  // Increments Counter
}

// Completed