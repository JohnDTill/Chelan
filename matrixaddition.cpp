#include "matrixaddition.h"

#include "chelan.h"

namespace Chelan {

MatrixAddition::MatrixAddition(const std::vector<Expr*>& args)
    : Expr(MATRIX_ADDITION), args(args){}

Expr* MatrixAddition::clone() const{
    return new MatrixAddition(cloneArgs(args));
}

Expr* MatrixAddition::evaluate(){
    for(std::vector<Expr*>::size_type i = args.size()-1; i < args.size(); i--){
        if(args[i]->type == MATRIX_NUMERIC){
            std::vector<mpq_class> vals = static_cast<MatrixNumeric*>(args[i])->args;
            std::vector<mpq_class>::size_type rows = static_cast<MatrixNumeric*>(args[i])->rows;
            std::vector<mpq_class>::size_type cols = static_cast<MatrixNumeric*>(args[i])->cols;
            delete args[i];
            args.erase(args.begin()+i);

            for(std::vector<Expr*>::size_type j = i-1; j < args.size(); j--){
                if(args[j]->type == MATRIX_NUMERIC){
                    Q_ASSERT(static_cast<MatrixNumeric*>(args[j])->rows == rows);
                    Q_ASSERT(static_cast<MatrixNumeric*>(args[j])->cols == cols);

                    std::vector<mpq_class>& es = static_cast<MatrixNumeric*>(args[j])->args;
                    for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++)
                        vals[k] += es[k];
                    delete args[j];
                    args.erase(args.begin()+j);
                }
            }

            args.push_back(new MatrixNumeric(rows, cols, vals));

            break;
        }
    }
    if(args.size()==1) return args[0];


    return nullptr;
}

QString MatrixAddition::toMathBran(Precedence) const{
    QString str = args.front()->toMathBran(PREC_ADDITION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        str += " + " + args[i]->toMathBran(PREC_ADDITION);

    return str;
}

}
