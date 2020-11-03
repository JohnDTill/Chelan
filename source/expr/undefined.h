#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "expr.h"

namespace Chelan{

class Undefined : public Expr{
public:
    const QString msg;
    const bool type_error;

public:
    Undefined(const QString& msg, bool type_error = false);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // UNDEFINED_H
