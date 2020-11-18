#include "assignelement.h"

#include <chelan.h>

namespace Chelan{

AssignElement::AssignElement(std::vector<Expr*>::size_type offset, Expr* rhs, Expr* index)
    : offset(offset), index(index), rhs(rhs){}

void AssignElement::execute(Runtime& runtime){
    Q_ASSERT(runtime.stack.size() >= offset);

    Expr* index_eval = Expr::evaluateAndFree( index->clone(), runtime );

    if(index_eval->type != RATIONAL){
        runtime.out << "ERROR: assignment subscript did not evaluate: " << index_eval->toMathBran();
        Expr::deleteRecursive(index_eval);
        throw 1;
    }

    mpq_class r = static_cast<Rational*>(index_eval)->value;
    delete index_eval;
    if(r.get_den() != 1){
        runtime.out << "ERROR: assignment subscript with non-integer index: " << r.get_str().c_str();
        throw 1;
    }else if(r < 0){
        runtime.out << "ERROR: assignment subscript with negative integer index: " << r.get_str().c_str();
        throw 1;
    }
    unsigned long long index = r.get_num().get_ui();

    Expr* mat = runtime.stack[runtime.stack.size() - offset];
    switch (mat->type) {
        case MATRIX_NUMERIC:{
            MatrixNumeric* mn = static_cast<MatrixNumeric*>(mat);
            if(mn->cols != 1 && mn->rows != 1){
                runtime.out << "ERROR: vector assignment to non-vector matrix: " << mn->toMathBran();
                throw 1;
            }

            std::vector<mpq_class>& args = mn->args;
            if(index >= args.size()){
                runtime.out << "ERROR: assignment subscript " << index
                            << " is greater than vector size " << args.size();
                throw 1;
            }

            Expr* rhs_eval = Expr::evaluateAndFree( rhs->clone(), runtime );

            if(rhs_eval->type != RATIONAL){
                runtime.out << "ERROR: subscript assignment of non-rational number: " << rhs_eval->toMathBran();
                Expr::deleteRecursive(rhs_eval);
                throw 1;
            }

            args[index] = static_cast<Rational*>(rhs_eval)->value;
            delete rhs_eval;

            return;
        }
        default:
            runtime.out << "ERROR: may only assign element to numeric matrix: " << mat->toMathBran();
            throw 1;
    }
}

}
