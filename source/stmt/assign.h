#ifndef ASSIGN_H
#define ASSIGN_H

#include "../stmt.h"

namespace Chelan {

class Assign : public Stmt{
private:
    std::vector<Expr*>::size_type offset;
    Expr* rhs;

public:
    Assign(std::vector<Expr*>::size_type offset, Expr* rhs);
    bool execute(Runtime& runtime) override final;
};

}

#endif // ASSIGN_H
