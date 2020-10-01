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
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;

private:
    virtual QString getKey(Precedence prec = PREC_NONE) const override;
};

}

#endif // POWER_H
