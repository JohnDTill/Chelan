#ifndef MATRIXNUMERIC_H
#define MATRIXNUMERIC_H

#include "expr.h"

namespace Chelan{

class MatrixNumeric : public Expr{
public:
    const std::vector<Expr*>::size_type rows;
    const std::vector<Expr*>::size_type cols;
    std::vector<Expr*> args;
    QString key;

public:
    MatrixNumeric(int rows, int cols, const std::vector<Expr*>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;
};

}

#endif // MATRIXNUMERIC_H
