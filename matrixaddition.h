#ifndef MATRIXADDITION_H
#define MATRIXADDITION_H

#include "expr.h"

namespace Chelan {

class MatrixAddition : public Expr{
public:
    std::vector<Expr*> args;

public:
    MatrixAddition(const std::vector<Expr*>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // MATRIXADDITION_H
