#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include "expr.h"

namespace Chelan {

class Transpose : public Expr{
public:
    Transpose();
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // TRANSPOSE_H
