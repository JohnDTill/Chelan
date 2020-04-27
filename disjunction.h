#ifndef DISJUNCTION_H
#define DISJUNCTION_H

#include "node.h"

namespace AST{

class Disjunction : public Node{
public:
    std::vector<Node*> args;
    QString key;

public:
    Disjunction();
    static Node* Or(Node* lhs, Node* rhs);
    static Node* Or(const std::vector<Node*>& args);
    void processNewArg(Node* n);
    virtual Node* clone() const override;
    virtual void deleteChildren() override;
    virtual Node* evaluate() override;
    virtual QString toString(Precedence prec = PREC_NONE) const override;

private:
    void flatten(Disjunction* d);
    void insertOrDiscard(Node* n);
    void setKey();
    static bool compare(const Node* a, const Node* b);
};

}

#endif // DISJUNCTION_H
