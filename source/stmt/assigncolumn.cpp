#include "assigncolumn.h"

#include <chelan.h>

namespace Chelan{

AssignColumn::AssignColumn(std::vector<Expr*>::size_type offset, Chelan::Expr* rhs, Chelan::Expr* index)
    : offset(offset), index(index), rhs(rhs){}

void AssignColumn::execute(Runtime& runtime){
    Q_ASSERT(runtime.stack.size() >= offset);

    Expr* index_eval = Expr::evaluateAndFree( index->clone(), runtime );

    if(index_eval->type != RATIONAL){
        runtime.out << "ERROR: assignment col did not evaluate: " << index_eval->toMathBran();
        Expr::deleteRecursive(index_eval);
        throw 1;
    }

    mpq_class r = static_cast<Rational*>(index_eval)->value;
    delete index_eval;
    if(r.get_den() != 1){
        runtime.out << "ERROR: assignment col with non-integer index: " << r.get_str().c_str();
        throw 1;
    }else if(r < 0){
        runtime.out << "ERROR: assignment col with negative integer index: " << r.get_str().c_str();
        throw 1;
    }
    unsigned long long index = r.get_num().get_ui();

    Expr* mat = runtime.stack[runtime.stack.size() - offset];
    switch (mat->type) {
        case MATRIX_NUMERIC:{
            MatrixNumeric* mn = static_cast<MatrixNumeric*>(mat);

            std::vector<mpq_class>& args = mn->args;
            if(index >= args.size()){
                runtime.out << "ERROR: assignment subscript " << index
                            << " is greater than vector size " << args.size();
                throw 1;
            }

            Expr* rhs_eval = Expr::evaluateAndFree( rhs->clone(), runtime );

            if(rhs_eval->type != MATRIX_NUMERIC){
                runtime.out << "ERROR: col assignment is not numeric matrix: " << rhs_eval->toMathBran();
                Expr::deleteRecursive(rhs_eval);
                throw 1;
            }

            MatrixNumeric* v = static_cast<MatrixNumeric*>(rhs_eval);
            if(v->cols != 1){
                runtime.out << "ERROR: vector assignment to non-vector matrix: " << v->toMathBran();
                delete v;
                throw 1;
            }else if(v->rows != mn->rows){
                runtime.out << "ERROR: vector assignment with " << mn->rows
                            << " on LHS and " << v->rows << " on RHS";
                delete v;
                throw 1;
            }

            for(unsigned long i = 0; i < v->rows; i++)
                args[index + i*mn->cols] = v->args[i];
            delete v;

            return;
        }
        default:
            runtime.out << "ERROR: may only assign column to numeric matrix: " << mat->toMathBran();
            throw 1;
    }
}

}
