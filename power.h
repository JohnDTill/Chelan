#ifndef POWER_H
#define POWER_H

#include "node.h"
#include <gmpxx.h>

namespace AST{

class Power : public Node{
public:
    Node* lhs;
    Node* rhs;

public:
    Power(Node* lhs, Node* rhs);
    static Node* Raise(Node* lhs, Node* rhs);
    static Node* Raise(Node* lhs, mpq_class rhs);
    virtual Node* clone() const override;
    virtual void deleteChildren() override;
    virtual Node* evaluate() override;
    virtual QString toString(Precedence = PREC_NONE) const override;

private:
    virtual QString getKey(Precedence prec = PREC_NONE) const override;
};

}

#endif // POWER_H
