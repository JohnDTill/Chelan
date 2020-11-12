#ifndef WHILE_H
#define WHILE_H

#include "../stmt.h"

namespace Chelan {

class While : public Stmt{
private:
    Expr* condition;
    Stmt* body;
    std::vector<Expr*>::difference_type stack_size;

public:
    While(Expr* condition, Stmt* body, std::vector<Expr*>::difference_type stack_size);
    virtual void execute(Runtime& runtime) override final;
};

}

#endif // WHILE_H
