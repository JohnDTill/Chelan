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
    Rational(int value);
    Rational(const QString& value);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // RATIONAL_H
