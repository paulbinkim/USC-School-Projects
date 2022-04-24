// If.cpp:
#include "If.h"
using namespace std;  // (PIAZZA says can use)

If::If(std::string variableName, std::string Op, int value, int line)
        : m_variableName(variableName), m_operator(Op), m_value(value), linenum(line) {}  // Constructor

void If::execute(ProgramState* state, std::ostream& outf) {
    int value = state->GetValue(m_variableName);

    if (m_operator == "<") {    // Checks "<" Operator
        if (value < m_value) {  // If passes sets counter to new line
            state->setCounter(linenum);
        } else {  // Else, goes to next line
            int counter = state->getCounter();
            state->setCounter(counter + 1);
        }
    } else if (m_operator == "<=") {  // Checks "<=" Operator
        if (value <= m_value) {
            state->setCounter(linenum);
        } else {
            int counter = state->getCounter();
            state->setCounter(counter + 1);
        }
    } else if (m_operator == ">") {  // Checks ">" Operator
        if (value > m_value) {
            state->setCounter(linenum);
        } else {
            int counter = state->getCounter();
            state->setCounter(counter + 1);
        }
    } else if (m_operator == ">=") {  // Checks ">=" Operator
        if (value >= m_value) {
            state->setCounter(linenum);
        } else {
            int counter = state->getCounter();
            state->setCounter(counter + 1);
        }
    } else if (m_operator == "==" || m_operator == "=") {  // There are inconsistencies in test cases therefore I did
                                                           // this.
        if (value == m_value) {
            state->setCounter(linenum);
        } else {
            int counter = state->getCounter();
            state->setCounter(counter + 1);
        }
    } else if (m_operator == "<>") {  // Checks "!=" Operator
        if (value != m_value) {
            state->setCounter(linenum);
        } else {
            int counter = state->getCounter();
            state->setCounter(counter + 1);
        }
    }
}

// Completed