#include "matrixmultiplication.h"

#include "chelan.h"

namespace Chelan {

template<typename ReturnType>
MatrixMultiplication<ReturnType>::MatrixMultiplication(const std::vector<Expr*>& args, Expr* scaling)
    : Expr(MATRIX_MULTIPLICATION), args(args), scaling(scaling){

}

template<typename ReturnType>
ReturnType* MatrixMultiplication<ReturnType>::clone() const{
    return new MatrixMultiplication<ReturnType>(cloneArgs(args), scaling->clone());
}

template<typename ReturnType>
ReturnType* MatrixMultiplication<ReturnType>::evaluate(){
    //Fast path//
    //Fold constants
    /*
    for(std::vector<Expr*>::size_type i = args.size()-1; i < args.size(); i--){
        if(i > 0 && args[i]->type == MATRIX_NUMERIC && args[i-1]->type == MATRIX_NUMERIC){
            MatrixNumeric* A = static_cast<MatrixNumeric*>(args[i-1]);
            MatrixNumeric* B = static_cast<MatrixNumeric*>(args[i]);

            if(cols != B->rows){
                err_msg += "SIZE ERROR: Multiplied matrices of incompatible sizes "
                        + QString::number(rows) + "×" + QString::number(cols)
                        + " and "
                        + QString::number(B->rows) + "×" + QString::number(B->cols)
                        + "\n";
                return new Undefined("", true);
            }

            std::vector<mpq_class> vals(rows * B->cols);

            for(std::vector<mpq_class>::size_type i = 0; i < rows; i++){
                for(std::vector<mpq_class>::size_type j = 0; j < B->cols; j++){
                    std::vector<mpq_class>::size_type index = i*B->cols + j;
                    vals[index] = at(i,0)*B->at(0,j);
                    for(std::vector<mpq_class>::size_type k = 1; k < cols; k++)
                        vals[index] += at(i,k)*B->at(k,j);
                }
            }

            args[i-1] = new MatrixNumeric(rows, B->cols, vals);
            delete A;
            delete B;
            args.erase(args.begin() + i);
        }
    }

    if(args.size()==1 && args[0]->type == MATRIX_NUMERIC && scaling->type == RATIONAL){
        mpq_class scaling = static_cast<Rational*>(scaling)->value;
        for(mpq_class& val : static_cast<MatrixNumeric*>(args[0])->args)
            val *= scaling;
        delete scaling;
        return evaluate(args[0]);
    }
    */

    return nullptr;
}

template<typename ReturnType>
void MatrixMultiplication<ReturnType>::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec > PREC_MULTIPLICATION) out << '(';
    if(scaling->type != RATIONAL || static_cast<Rational*>(scaling)->value != 1)
        scaling->writeMathBran(out, PREC_MULTIPLICATION);
    for(Expr* e : args)
        e->writeMathBran(out, PREC_MULTIPLICATION);
    if(prec > PREC_MULTIPLICATION) out << ')';
}

}
