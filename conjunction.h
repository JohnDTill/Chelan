#ifndef CONJUNCTION_H
#define CONJUNCTION_H

#include "node.h"

namespace AST{

class Conjunction : public Node{
public:
    std::vector<Node*> args;
    QString key;

public:
    Conjunction();
    static Node* And(Node* lhs, Node* rhs);
    static Node* And(const std::vector<Node*>& args);
    void processNewArg(Node* n);
    virtual Node* clone() const override;
    virtual void deleteChildren() override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;

private:
    void flatten(Conjunction* c);
    void insertOrDiscard(Node* n);
    void setKey();
    static bool compare(const Node* a, const Node* b);
};

}

#endif // CONJUNCTION_H
