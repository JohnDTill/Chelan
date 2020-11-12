#ifndef RETURN_H
#define RETURN_H

#include "../stmt.h"

#include "../expr.h"

namespace Chelan {

class Return : public Stmt{
public:
    Expr* e;
    std::vector<Expr*>::size_type stack_size;

public:
    Return(Expr* e, std::vector<Expr*>::size_type stack_size);
    virtual void execute(Runtime& runtime) override final;
};

}

#endif // RETURN_H
