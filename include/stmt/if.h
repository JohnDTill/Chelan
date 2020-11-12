#ifndef IF_H
#define IF_H

#include "../stmt.h"

namespace Chelan {

class If : public Stmt{
private:
    Expr* condition;
    Stmt* then;
    Stmt* el;
    std::vector<Expr*>::difference_type stack_size;

public:
    If(Expr* condition, Stmt* then, Stmt* el, std::vector<Expr*>::difference_type stack_size);
    void execute(Runtime& runtime) override final;
};

}

#endif // IF_H
