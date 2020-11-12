#ifndef ABSOLUTEVALUE_H
#define ABSOLUTEVALUE_H
#include "expr.h"

namespace Chelan{

class AbsoluteValue : public Expr{
public:
    Expr* e;

public:
    AbsoluteValue(Expr* e);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime& runtime) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // ABSOLUTEVALUE_H
