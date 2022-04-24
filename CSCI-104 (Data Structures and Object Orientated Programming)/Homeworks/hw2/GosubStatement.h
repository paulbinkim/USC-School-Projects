#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class GosubStatement : public Statement {
private:
    int linenum;

public:
    virtual void execute(ProgramState* state, std::ostream& outf);
    GosubStatement(int line);
};

#endif

// Completed