#ifndef MATRIXMULTIPLICATION_H
#define MATRIXMULTIPLICATION_H

#include "expr.h"

namespace Chelan {

template<typename ReturnType>
class MatrixMultiplication : public ReturnType{
public:
    std::vector<Expr*> args;
    Expr* scaling;

public:
    MatrixMultiplication(const std::vector<Expr*>& args, Expr* scaling);
    virtual ReturnType* clone() const override;
    virtual ReturnType* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // MATRIXMULTIPLICATION_H
