#ifndef NEGATION_H
#define NEGATION_H

#include "node.h"

namespace AST{

class Negation : public Node{
public:
    Node* n;

public:
    Negation(Node* n);
    static Node* Not(Node* n);
    virtual Node* clone() const override;
    virtual void deleteChildren() override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;
};

}

#endif // NEGATION_H
