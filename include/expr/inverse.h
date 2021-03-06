#ifndef INVERSE_H
#define INVERSE_H

#include "expr.h"

namespace Chelan{

class Inverse : public Expr{
private:
    Expr* e;

public:
    Inverse(Expr* e);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate(Runtime& runtime) override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // INVERSE_H
