#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class If : public Statement {
public:
    virtual void execute(ProgramState* state, std::ostream& outf);
    If(std::string variableName, std::string Op, int value, int line);

private:
    std::string m_variableName;
    std::string m_operator;
    int m_value;
    int linenum;
};

#endif

// Completed