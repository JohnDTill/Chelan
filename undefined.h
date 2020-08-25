#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "node.h"

namespace AST{

class Undefined : public Node{
private:
    const QString msg;

public:
    Undefined(const QString& msg);
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // UNDEFINED_H
