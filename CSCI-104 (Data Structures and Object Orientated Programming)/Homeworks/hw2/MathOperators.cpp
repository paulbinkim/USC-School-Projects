// MathOperators.cpp:
#include "MathOperators.h"
using namespace std;  // (PIAZZA says can use)

MathOperators::MathOperators(std::string variableName, std::string variableName2, std::string mathoperator)
        : m_variableName(variableName), m_variableName2(variableName2), m_mathOperators(mathoperator) {}  // Constructor

void MathOperators::execute(ProgramState* state, std::ostream& outf) {
    // Implementation Details that check for specifics (ADD, SUB, MULT, DIV)
    if (m_mathOperators == "ADD") {
        state->Add(m_variableName, m_variableName2);
    } else if (m_mathOperators == "SUB") {
        state->Sub(m_variableName, m_variableName2);
    } else if (m_mathOperators == "MULT") {
        state->Mult(m_variableName, m_variableName2);
    } else if (m_mathOperators == "DIV") {
        state->Div(m_variableName, m_variableName2);
    }

    int counter = state->getCounter();
    state->setCounter(counter + 1);  // Increments Counter by 1.
}

// Completed