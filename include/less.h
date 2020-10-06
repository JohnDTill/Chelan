#ifndef LESS_H
#define LESS_H

#include "expr.h"

namespace Chelan{

class Less : public Expr{
private:
    Expr* n;

public:
    Less(Expr* n);
    static Expr* IsLess(Expr* lhs, Expr* rhs);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // LESS_H
