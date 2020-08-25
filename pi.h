#ifndef PI_H
#define PI_H

#include "node.h"

namespace AST{

class Pi : public Node{
public:
    Pi();
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // PI_H
