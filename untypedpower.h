#ifndef UNTYPEDPOWER_H
#define UNTYPEDPOWER_H

#include "expr.h"

namespace Chelan {

class UntypedPower : public Expr{
public:
    Expr* lhs;
    Expr* rhs;

public:
    UntypedPower(Expr* lhs, Expr* rhs);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;
    Expr* evaluate(QString& err_msg);
};

}

#endif // UNTYPEDPOWER_H
