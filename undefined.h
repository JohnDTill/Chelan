#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "expr.h"

namespace Chelan{

class Undefined : public Expr{
public:
    const QString msg;

public:
    Undefined(const QString& msg);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // UNDEFINED_H
