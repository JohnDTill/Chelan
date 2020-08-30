#include "matrixenumeration.h"

#include "chelan.h"

namespace Chelan{

MatrixEnumeration::MatrixEnumeration(int rows, int cols, const std::vector<Expr*>& args)
    : Expr(MATRIX_ENUMERATION),
      num_v(rows),
      num_h(cols),
      args(args){}

Expr* MatrixEnumeration::clone() const{
    std::vector<Expr*> cloned_args;
    for(Expr* n : args) cloned_args.push_back(n->clone());
    return new MatrixEnumeration(num_v, num_h, cloned_args);
}

Expr* MatrixEnumeration::evaluate(){
    if(num_v == 1 && num_h == 1) return args[0];

    bool numeric = true;
    for(Expr* expr : args){
        if(expr->type != RATIONAL){
            numeric = false;
            break;
        }
    }
    if(numeric) return new MatrixNumeric(num_v, num_h, args);

    //DO THIS: CHECK FOR SIZE ERRORS
    //Want special rules for 0's and 1's: ⁜⊞⏴2⏵⏴2⏵⏴R⏵⏴p⏵⏴0⏵⏴1⏵ bold zero and size appropriately

    flatten();

    return nullptr;
}

QString MatrixEnumeration::toMathBran(Expr::Precedence) const{
    QString str = "⁜⊞⏴" + QString::number(num_v) + "⏵⏴" + QString::number(num_h) + "⏵";
    for(Expr* n : args) str += "⏴" + n->toMathBran() + "⏵";
    return str;
}

void MatrixEnumeration::visitChildren(Interpreter* interpreter){
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        args[i] = interpreter->evaluate(args[i]);
}

void MatrixEnumeration::flatten(){
    for(std::vector<Expr*>::size_type i = 0; i < num_h; i++){
        for(std::vector<Expr*>::size_type j = 0; j < num_v; j++){
            std::vector<Expr*>::size_type index = i*num_v + j;
            if(args[index]->type == MATRIX_ENUMERATION){
                //Can't always flatten: ⁜⊞⏴2⏵⏴2⏵⏴R⏵⏴p⏵⏴⁜⊞⏴1⏵⏴3⏵⏴0⏵⏴0⏵⏴0⏵⏵⏴1⏵
                //Sometimes can: ⁜⊞⏴2⏵⏴1⏵⏴a⏵⏴⁜⊞⏴2⏵⏴1⏵⏴1⏵⏴0⏵⏵
            }
        }
    }
}

}