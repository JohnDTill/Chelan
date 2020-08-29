#ifndef NEGATION_H
#define NEGATION_H

#include "expr.h"

namespace Chelan{

class Negation : public Expr{
public:
    Expr* n;

public:
    Negation(Expr* n);
    static Expr* Not(Expr* n);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;
};

}

#endif // NEGATION_H
