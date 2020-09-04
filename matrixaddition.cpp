#include "matrixaddition.h"

#include "chelan.h"

namespace Chelan {

MatrixAddition::MatrixAddition(const std::vector<Expr*>& args)
    : Expr(MATRIX_ADDITION, MATRIX), args(args){}

Expr* MatrixAddition::clone() const{
    return new MatrixAddition(cloneArgs(args));
}

Expr* MatrixAddition::evaluate(){
    //Moved
    return nullptr;
}

QString MatrixAddition::toMathBran(Expr::Precedence) const{
    QString str = args.front()->toMathBran(PREC_ADDITION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        str += " + " + args[i]->toMathBran(PREC_ADDITION);

    return str;
}

void MatrixAddition::visitChildren(Interpreter* interpreter){
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        args[i] = interpreter->evaluate(args[i]);
}

}
