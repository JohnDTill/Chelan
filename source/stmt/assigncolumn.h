#ifndef ASSIGNCOLUMN_H
#define ASSIGNCOLUMN_H

#include "../stmt.h"

namespace Chelan{

class AssignColumn : public Stmt{
private:
    std::vector<Expr*>::size_type offset;
    Expr* index;
    Expr* rhs;

public:
    AssignColumn(std::vector<Expr*>::size_type offset, Expr* rhs, Expr* index);
    void execute(Runtime& runtime) override final;
};

}

#endif // ASSIGNCOLUMN_H
