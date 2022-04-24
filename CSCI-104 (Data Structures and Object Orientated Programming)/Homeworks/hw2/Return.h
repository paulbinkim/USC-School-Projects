#ifndef RETURN_STATEMENT_INCLUDED
#define RETURN_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class Return : public Statement {
public:
    virtual void execute(ProgramState* state, std::ostream& outf);
    Return();
};

#endif

// Completed