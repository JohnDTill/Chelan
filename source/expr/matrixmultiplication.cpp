#include "matrixmultiplication.h"

#include "chelan.h"

namespace Chelan {

MatrixMultiplication::MatrixMultiplication(const std::vector<Expr*>& args, Expr* scaling)
    : Expr(MATRIX_MULTIPLICATION), args(args), scaling(scaling){

}

Expr* MatrixMultiplication::clone() const{
    return new MatrixMultiplication(cloneArgs(args), scaling->clone());
}

Expr* MatrixMultiplication::evaluate(Runtime& runtime){
    evaluateAndFreeArgs(args, runtime);
    scaling = Expr::evaluateAndFree(scaling, runtime);

    //Fast path//
    //Fold constants
    for(std::vector<Expr*>::size_type i = args.size()-1; i < args.size(); i--){
        if(i > 0 && args[i]->type == MATRIX_NUMERIC && args[i-1]->type == MATRIX_NUMERIC){
            MatrixNumeric* A = static_cast<MatrixNumeric*>(args[i-1]);
            MatrixNumeric* B = static_cast<MatrixNumeric*>(args[i]);

            std::vector<mpq_class> vals(A->rows * B->cols);

            for(std::vector<mpq_class>::size_type i = 0; i < A->rows; i++){
                for(std::vector<mpq_class>::size_type j = 0; j < B->cols; j++){
                    std::vector<mpq_class>::size_type index = i*B->cols + j;
                    vals[index] = A->at(i,0)*B->at(0,j);
                    for(std::vector<mpq_class>::size_type k = 1; k < A->cols; k++)
                        vals[index] += A->at(i,k)*B->at(k,j);
                }
            }

            if(A->rows > 1 || B->cols > 1){
                args[i-1] = new MatrixNumeric(A->rows, B->cols, vals);
                delete A;
                delete B;
                args.erase(args.begin() + i);
            }else{
                scaling = new ScalarMultiplication({scaling, vals[0]});
                args.erase(args.begin() + i - 1, args.begin() + i + 1);
            }
        }
    }

    if(args.size()==0){
        return scaling;
    }else if(args.size()==1 && args[0]->type == MATRIX_NUMERIC && scaling->type == RATIONAL){
        mpq_class coeff = static_cast<Rational*>(scaling)->value;
        for(mpq_class& val : static_cast<MatrixNumeric*>(args[0])->args)
            val *= coeff;
        delete scaling;
        return args[0];
    }

    return nullptr;
}

void MatrixMultiplication::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec > PREC_MULTIPLICATION) out << '(';
    if(scaling->type != RATIONAL || static_cast<Rational*>(scaling)->value != 1)
        scaling->writeMathBran(out, PREC_MULTIPLICATION);
    for(Expr* e : args)
        e->writeMathBran(out, PREC_MULTIPLICATION);
    if(prec > PREC_MULTIPLICATION) out << ')';
}

}
