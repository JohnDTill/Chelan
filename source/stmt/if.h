#ifndef IF_H
#define IF_H

#include "../stmt.h"

namespace Chelan {

class If : public Stmt{
private:
    Expr* condition;
    Stmt* then;
    Stmt* el;

public:
    If(Expr* condition, Stmt* then, Stmt* el);
    bool execute(Runtime& runtime) override final;
};

}

#endif // IF_H
