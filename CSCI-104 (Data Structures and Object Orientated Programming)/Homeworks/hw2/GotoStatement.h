#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class GotoStatement : public Statement {
private:
    int linenum;

public:
    GotoStatement(int line);
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif

// Completed