#ifndef REALVARIABLE_H
#define REALVARIABLE_H

#include "node.h"

namespace AST{

typedef QChar ID;

class RealVariable : public Node{
public:
    const ID name;

public:
    RealVariable(const ID& name);
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // REALVARIABLE_H
