#ifndef MATRIX_H
#define MATRIX_H

#include "expr.h"

namespace Chelan{

class MatrixEnumeration : public Expr{
public:
    const std::vector<Expr*>::size_type num_v; //These are not the size because matrices can nest
    const std::vector<Expr*>::size_type num_h;
    std::vector<Expr*> args;
    QString key;

public:
    MatrixEnumeration(int num_v, int num_h, const std::vector<Expr*>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;

private:
    void flatten();
};

}

#endif // MATRIX_H
