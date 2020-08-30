#ifndef EQUALS_H
#define EQUALS_H

#include "expr.h"

namespace Chelan{

class Equality : public Expr{
private:
    Expr* n;

public:
    Equality(Expr* n);
    static Expr* Equals(Expr* lhs, Expr* rhs);
    static Expr* EqualsZero(Expr* n);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;
};

}

#endif // EQUALS_H
