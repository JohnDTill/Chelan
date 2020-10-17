#ifndef MATRIX_H
#define MATRIX_H

#include "expr.h"

namespace Chelan{

class MatrixEnumeration : public Expr{
public:
    const vInt num_v; //These are not the size because matrices can nest
    const vInt num_h;
    std::vector<Expr*> args;
    QString key;

public:
    MatrixEnumeration(vInt num_v, vInt num_h, const std::vector<Expr*>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;

private:
    void flatten();
};

}

#endif // MATRIX_H
