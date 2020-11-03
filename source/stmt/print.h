#ifndef PRINT_H
#define PRINT_H

#include "../stmt.h"

#include "../expr.h"

namespace Chelan {

class Print : public Stmt{
private:
    Expr* e;

public:
    Print(Expr* e);
    virtual bool execute(Runtime& runtime) override final;
};

}

#endif
