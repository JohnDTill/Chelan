#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

namespace AST{

class Matrix : public Node{
public:
    const int rows;
    const int cols;
    std::vector<Node*> args;
    QString key;

public:
    Matrix(int rows, int cols, std::vector<Node*> children);
    virtual Node* clone() const override;
    virtual Node* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
};

}

#endif // MATRIX_H
