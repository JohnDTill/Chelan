#ifndef MATRIX_H
#define MATRIX_H

#include "expr.h"

namespace Chelan{

class Matrix : public Expr{
public:
    const int rows;
    const int cols;
    std::vector<Expr*> args;
    QString key;

public:
    Matrix(int rows, int cols, std::vector<Expr*> children);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;
};

}

#endif // MATRIX_H
