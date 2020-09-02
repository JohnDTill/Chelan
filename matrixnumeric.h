#ifndef MATRIXNUMERIC_H
#define MATRIXNUMERIC_H

#include "expr.h"
#include <gmpxx.h>

namespace Chelan{

class MatrixNumeric : public Expr{
public:
    const std::vector<mpq_class>::size_type rows;
    const std::vector<mpq_class>::size_type cols;
    std::vector<mpq_class> args;
    QString key;

public:
    MatrixNumeric(int rows, int cols, const std::vector<mpq_class>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter*) override;
    const mpq_class& at(std::vector<mpq_class>::size_type row,
                        std::vector<mpq_class>::size_type col) const;
};

}

#endif // MATRIXNUMERIC_H
