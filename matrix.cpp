#include "matrix.h"

#include "chelan.h"

namespace AST{

Matrix::Matrix(int rows, int cols, std::vector<Node*> children)
    : Node(MATRIX),
      rows(rows),
      cols(cols),
      args(children){}

Node* Matrix::clone() const{
    std::vector<Node*> cloned_args;
    for(Node* n : args) cloned_args.push_back(n->clone());
    return new Matrix(rows, cols, cloned_args);
}

Node* Matrix::evaluate(){
    return nullptr;
}

QString Matrix::toMathBran(Node::Precedence) const{
    QString str = "⁜⊞⏴" + QString::number(rows) + "⏵⏴" + QString::number(cols) + "⏵";
    for(Node* n : args) str += "⏴" + n->toMathBran() + "⏵";
    return str;
}

}
