#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "expr.h"

namespace Chelan{

class Boolean : public Expr{
public:
    const bool value;

public:
    Boolean(const bool& value);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // BOOLEAN_H
