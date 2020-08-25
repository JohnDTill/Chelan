#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "node.h"

namespace AST{

class Boolean : public Node{
public:
    const bool value;

public:
    Boolean(const bool& value);
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // BOOLEAN_H
