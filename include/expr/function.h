#ifndef FUNCTION_H
#define FUNCTION_H

#include "expr.h"

namespace Chelan{

class Stmt;

class Function : public Expr{
public:
    Stmt* body;

public:
    Function(Stmt* body);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // FUNCTION_H
