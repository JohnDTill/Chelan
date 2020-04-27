#ifndef CONDITIONALVALUE_H
#define CONDITIONALVALUE_H

#include "node.h"

namespace AST{

class ConditionalValue : public Node{
private:
    std::vector<Node*> values;
    std::vector<Node*> conditions;

public:
    ConditionalValue();
    ConditionalValue(Node* condition, Node* value_true, Node* value_false);
    static Node* Ternary(Node* condition, Node* value_true, Node* value_false);
    virtual Node* clone() const override;
    virtual void deleteChildren() override;
    virtual Node* evaluate() override;
    virtual QString toString(Precedence = PREC_NONE) const override;
};

}

#endif // CONDITIONALVALUE_H
