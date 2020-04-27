#ifndef EQUALS_H
#define EQUALS_H

#include "node.h"

namespace AST{

class Equality : public Node{
private:
    Node* n;

public:
    Equality(Node* n);
    static Node* Equals(Node* lhs, Node* rhs);
    static Node* EqualsZero(Node* n);
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toString(Precedence prec = PREC_NONE) const override;
};

}

#endif // EQUALS_H
