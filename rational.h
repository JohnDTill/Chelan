#ifndef RATIONAL_H
#define RATIONAL_H

#include "node.h"
#include <gmpxx.h>

namespace AST{

class Rational : public Node{
public:
    const mpq_class value;

public:
    Rational(const mpq_class& value);
    Rational(const QString& value);
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toString(Precedence = PREC_NONE) const override;
};

}

#endif // RATIONAL_H
