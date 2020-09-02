#include "matrixmultiplication.h"

#include "chelan.h"

namespace Chelan {

MatrixMultiplication::MatrixMultiplication(const std::vector<Expr*>& args, Expr* scaling)
    : Expr(MATRIX_MULTIPLICATION), args(args), scaling(scaling){

}

Expr* MatrixMultiplication::clone() const{
    return new MatrixMultiplication(cloneArgs(args), scaling->clone());
}

Expr* MatrixMultiplication::evaluate(){
    //Moved
    return nullptr;
}

QString MatrixMultiplication::toMathBran(Expr::Precedence) const{
    QString str = scaling->type == RATIONAL && static_cast<Rational*>(scaling)->value == 1 ?
                  "" :
                  args.front()->toMathBran(PREC_MULTIPLICATION);
    for(Expr* e : args)
        str += e->toMathBran(PREC_MULTIPLICATION);

    return str;
}

void MatrixMultiplication::visitChildren(Interpreter* interpreter){
    scaling = interpreter->evaluate(scaling);
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        args[i] = interpreter->evaluate(args[i]);
}

}
