#ifndef READVARIABLE_H
#define READVARIABLE_H

#include "expr.h"

namespace Chelan {

class Read : public Expr{
public:
    Expr*& var;

public:
    Read(Expr*& var);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // READVARIABLE_H
