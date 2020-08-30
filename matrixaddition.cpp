#include "matrixaddition.h"

#include "chelan.h"

namespace Chelan {

MatrixAddition::MatrixAddition(const std::vector<Expr*>& args)
    : Expr(MATRIX_ADDITION), args(args){

}

Expr* MatrixAddition::clone() const{
    return new MatrixAddition(args);
}

Expr* MatrixAddition::evaluate(){
    //Fast path//
    foldConstants();
    if(args.size()==1) return args[0];

    //Symbolic//
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

void MatrixAddition::foldConstants(){
    for(std::vector<Expr*>::size_type i = args.size()-1; i < args.size(); i--){
        if(args[i]->type == MATRIX_NUMERIC){
            std::vector<Expr*>& es = static_cast<MatrixNumeric*>(args[i])->args;
            std::vector<Expr*>::size_type rows = static_cast<MatrixNumeric*>(args[i])->rows;
            std::vector<Expr*>::size_type cols = static_cast<MatrixNumeric*>(args[i])->cols;
            std::vector<mpq_class> vals(es.size());
            for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++){
                vals[k] = static_cast<Rational*>(es[k])->value;
                delete es[k];
            }
            delete args[i];
            args.erase(args.begin()+i);

            for(std::vector<Expr*>::size_type j = i-1; j < args.size(); j--){
                if(args[j]->type == MATRIX_NUMERIC){
                    if(static_cast<MatrixNumeric*>(args[j])->rows != rows ||
                       static_cast<MatrixNumeric*>(args[j])->cols != cols){
                        //DO THIS: size error
                    }

                    std::vector<Expr*>& es = static_cast<MatrixNumeric*>(args[j])->args;
                    for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++){
                        vals[k] += static_cast<Rational*>(es[k])->value;
                        delete es[k];
                    }
                    delete args[j];
                    args.erase(args.begin()+j);
                }
            }

            std::vector<Expr*> ex(vals.size());
            for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++)
                ex[k] = new Rational(vals[k]);

            args.push_back(new MatrixNumeric(rows, cols, ex));

            break;
        }
    }
}

}
