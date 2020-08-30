#include "matrix.h"

#include "chelan.h"

namespace Chelan{

Matrix::Matrix(int rows, int cols, std::vector<Expr*> children)
    : Expr(MATRIX_ENUMERATION),
      rows(rows),
      cols(cols),
      args(children){}

Expr* Matrix::clone() const{
    std::vector<Expr*> cloned_args;
    for(Expr* n : args) cloned_args.push_back(n->clone());
    return new Matrix(rows, cols, cloned_args);
}

Expr* Matrix::evaluate(){
    return nullptr;
}

QString Matrix::toMathBran(Expr::Precedence) const{
    QString str = "⁜⊞⏴" + QString::number(rows) + "⏵⏴" + QString::number(cols) + "⏵";
    for(Expr* n : args) str += "⏴" + n->toMathBran() + "⏵";
    return str;
}

void Matrix::visitChildren(Interpreter* interpreter){
    for(Expr* expr : args) expr = interpreter->evaluate(expr);
}

}
