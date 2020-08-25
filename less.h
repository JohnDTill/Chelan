#ifndef LESS_H
#define LESS_H

#include "node.h"

namespace AST{

class Less : public Node{
private:
    Node* n;

public:
    Less(Node* n);
    static Node* IsLess(Node* lhs, Node* rhs);
    static Node* IsLessThanZero(Node* n);
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;
};

}

#endif // LESS_H
