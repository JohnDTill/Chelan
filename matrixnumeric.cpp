#include "matrixnumeric.h"

#include "chelan.h"

namespace Chelan{

MatrixNumeric::MatrixNumeric(int rows, int cols, const std::vector<Expr*>& args)
    : Expr(MATRIX_NUMERIC),
      rows(rows),
      cols(cols),
      args(args){}

Expr* MatrixNumeric::clone() const{
    std::vector<Expr*> cloned_args;
    for(Expr* n : args) cloned_args.push_back(n->clone());
    return new MatrixNumeric(rows, cols, cloned_args);
}

Expr* MatrixNumeric::evaluate(){
    return nullptr;
}

QString MatrixNumeric::toMathBran(Expr::Precedence) const{
    QString str = "⁜⊞⏴" + QString::number(rows) + "⏵⏴" + QString::number(cols) + "⏵";
    for(Expr* n : args) str += "⏴" + n->toMathBran() + "⏵";
    return str;
}

void MatrixNumeric::visitChildren(Interpreter* interpreter){
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        args[i] = interpreter->evaluate(args[i]);
}

}
