// LetStatement.cpp:
#include "LetStatement.h"
using namespace std;  // (PIAZZA says can use)

LetStatement::LetStatement(std::string variableName, int value)
        : m_variableName(variableName), m_value(value) {}  // Constructor

void LetStatement::execute(ProgramState* state, ostream& outf) {
    state->InsertMap(m_variableName, m_value);  // Inserts variable and value to a map.
    int counter = state->getCounter();
    state->setCounter(counter + 1);  // Increments program line by 1
}

// Completed
