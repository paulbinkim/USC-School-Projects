#ifndef PRINTALL_STATEMENT_INCLUDED
#define PRINTALL_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <iostream>

class PrintAllstatement : public Statement {
public:
    PrintAllstatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif

// Completed