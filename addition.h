#ifndef ADDITION_H
#define ADDITION_H

#include "node.h"
#include <gmpxx.h>

namespace AST{

class Addition : public Node{
public:
    std::vector<Node*> args;
    mpq_class constant = 0;
    QString key;

public:
    Addition(const std::vector<Node*>& args);
    static Node* Add(Node* lhs, Node* rhs);
    static Node* Add(Node* lhs, mpq_class rhs);
    static Node* Add(mpq_class lhs, Node* rhs);
    static Node* Add(const std::vector<Node*>& args);
    static Node* Subtract(Node* lhs, Node* rhs);
    virtual Node* clone() const override;
    virtual void deleteChildren() override;
    virtual Node* evaluate() override;
    virtual QString toString(Precedence prec = PREC_NONE) const override;

private:
    void foldConstants();
    void flatten();
    void flatten(Addition* a, std::vector<Node*>& new_args);
    void collect();
    void collect(int start, int end);
    void setKey();
};

}

#endif // ADDITION_H
