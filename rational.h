#ifndef RATIONAL_H
#define RATIONAL_H

#include "expr.h"
#include <gmpxx.h>

namespace Chelan{

class Rational : public Expr{
public:
    const mpq_class value;

public:
    Rational(const mpq_class& value);
    Rational(const QString& value);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter*) override;
};

}

#endif // RATIONAL_H
