#ifndef MATRIXNUMERIC_H
#define MATRIXNUMERIC_H

#include "expr.h"
#include <gmpxx.h>

namespace Chelan{

class MatrixNumeric : public Expr{
public:
    const vInt rows;
    const vInt cols;
    std::vector<mpq_class> args;
    QString key;

public:
    MatrixNumeric(vInt rows, vInt cols, const std::vector<mpq_class>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
    const mpq_class& at(std::vector<mpq_class>::size_type row,
                        std::vector<mpq_class>::size_type col) const;
};

}

#endif // MATRIXNUMERIC_H
