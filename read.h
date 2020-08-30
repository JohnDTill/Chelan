#ifndef READVARIABLE_H
#define READVARIABLE_H

#include "expr.h"

namespace Chelan {

class Read : public Expr{
public:
    const std::vector<Expr*>::size_type slot;
public:
    Read(std::vector<Expr*>::size_type slot);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;
};

}

#endif // READVARIABLE_H
