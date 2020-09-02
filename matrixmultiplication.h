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
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter*interpreter) override;
};

}

#endif // MATRIXMULTIPLICATION_H
