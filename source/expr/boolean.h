#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "expr.h"

namespace Chelan{

class Boolean : public Expr{
public:
    const bool value;

public:
    Boolean(const bool& value);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
    virtual bool isDefinitivelyFalse() const override {return !value;}
    virtual bool isDefinitivelyTrue() const override {return value;}
};

}

#endif // BOOLEAN_H
