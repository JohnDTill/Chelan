#ifndef PI_H
#define PI_H

#include "expr.h"

namespace Chelan{

class Pi : public Expr{
public:
    Pi();
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // PI_H
