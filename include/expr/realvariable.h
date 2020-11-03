#ifndef REALVARIABLE_H
#define REALVARIABLE_H

#include "expr.h"

namespace Chelan{

typedef QString ID;

class RealVariable : public Expr{
public:
    const ID name;

public:
    RealVariable(const ID& name);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // REALVARIABLE_H
