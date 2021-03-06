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
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // EQUALS_H
