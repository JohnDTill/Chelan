#ifndef ASSIGNELEMENT_H
#define ASSIGNELEMENT_H

#include "../stmt.h"

namespace Chelan{

class AssignElement : public Stmt{
private:
    std::vector<Expr*>::size_type offset;
    Expr* index;
    Expr* rhs;

public:
    AssignElement(std::vector<Expr*>::size_type offset, Expr* rhs, Expr* index);
    void execute(Runtime& runtime) override final;
};

}

#endif // ASSIGNELEMENT_H
