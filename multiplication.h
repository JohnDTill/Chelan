#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "node.h"
#include "undefined.h"
#include <gmpxx.h>

namespace AST{

class Multiplication : public Node{
public:
    std::vector<Node*> args;
    QString key;
    mpq_class constant = 1;

public:
    Multiplication(const std::vector<Node*>& args);
    static Node* Multiply(Node* lhs, Node* rhs);
    static Node* Multiply(mpq_class lhs, Node* rhs);
    static Node* Multiply(const std::vector<Node*>& args);
    static Node* Divide(Node* lhs, Node* rhs);
    virtual Node* clone() const override;
    virtual void deleteChildren() override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;

private:
    void foldConstants();
    void flatten();
    void flatten(Multiplication* a, std::vector<Node*>& new_args);
    void collect();
    void collect(int start, int end);
    void setKey();
    virtual QString getKey(Precedence prec = PREC_NONE) const override;
};

}

#endif // MULTIPLICATION_H
