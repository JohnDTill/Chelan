#ifndef MATRIXADDITION_H
#define MATRIXADDITION_H

#include "expr.h"

namespace Chelan {

class MatrixAddition : public Expr{
private:
    std::vector<Expr*> args;

public:
    MatrixAddition(const std::vector<Expr*>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter*interpreter) override;

private:
    void foldConstants();
};

}

#endif // MATRIXADDITION_H
