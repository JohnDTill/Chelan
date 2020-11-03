#ifndef WHILE_H
#define WHILE_H

#include "../stmt.h"

namespace Chelan {

class While : public Stmt{
private:
    Expr* condition;
    Stmt* body;

public:
    While(Expr* condition, Stmt* body);
    virtual bool execute(Runtime& runtime) override final;
};

}

#endif // WHILE_H
