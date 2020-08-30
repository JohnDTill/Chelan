#ifndef POWER_H
#define POWER_H

#include "expr.h"
#include <gmpxx.h>

namespace Chelan{

class ScalarPower : public Expr{
public:
    Expr* lhs;
    Expr* rhs;

public:
    ScalarPower(Expr* lhs, Expr* rhs);
    static Expr* Raise(Expr* lhs, Expr* rhs);
    static Expr* Raise(Expr* lhs, mpq_class rhs);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;

private:
    virtual QString getKey(Precedence prec = PREC_NONE) const override;
};

}

#endif // POWER_H
