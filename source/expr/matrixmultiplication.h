#ifndef MATRIXMULTIPLICATION_H
#define MATRIXMULTIPLICATION_H

#include "expr.h"

namespace Chelan {

class MatrixMultiplication : public Expr{
public:
    std::vector<Expr*> args;
    Expr* scaling;

public:
    MatrixMultiplication(const std::vector<Expr*>& args, Expr* scaling);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // MATRIXMULTIPLICATION_H
