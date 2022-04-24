#ifndef MATHOPERATORS_STATEMENT_INCLUDED
#define MATHOPERATORS_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class MathOperators : public Statement {
private:
    std::string m_variableName;
    std::string m_mathOperators;
    std::string m_variableName2;

public:
    MathOperators(std::string variableName, std::string variableName2, std::string mathoperator);
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif

// Completed