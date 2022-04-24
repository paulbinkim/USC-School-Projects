// Return.cpp:
#include "Return.h"
using namespace std;  // (PIAZZA says can use)

Return::Return() {}  // Constructor

void Return::execute(ProgramState* state, std::ostream& outf) {
    int linenum = state->PopStack();  // Calls function that Pops the top object of stack
    state->setCounter(linenum);       // Already iterated in GoSub to new line number so sets to old "popped value"
}

// Completed