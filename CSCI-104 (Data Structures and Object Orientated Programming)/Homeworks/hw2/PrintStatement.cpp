// PrintStatement.cpp:
#include "PrintStatement.h"
using namespace std;  // (PIAZZA says can use)

PrintStatement::PrintStatement(std::string variableName) : m_variableName(variableName) {}  // Constructor

void PrintStatement::execute(ProgramState* state, std::ostream& outf) {
    state->Print(m_variableName);  // Print Variable
    int counter = state->getCounter();
    state->setCounter(counter + 1);  // Increment counter
}

// Completed
