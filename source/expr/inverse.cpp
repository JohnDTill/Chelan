#include "inverse.h"

#include <chelan.h>

namespace Chelan {

Inverse::Inverse(Expr* e)
    : Expr(INVERSE), e(e) {}

Expr* Inverse::clone() const{
    return new Inverse(e->clone());
}

void Inverse::deleteChildren(){
    e->deleteChildren();
    delete e;
}

Expr* Inverse::evaluate(Runtime& runtime){
    e = Expr::evaluateAndFree(e, runtime);

    switch (e->type) {
        case MATRIX_NUMERIC:{
            MatrixNumeric* m = static_cast<MatrixNumeric*>(e);
            if(m->rows != m->cols){
                runtime.out << "ERROR: tried to invert non-square matrix: " << e->toMathBran();
                throw 1;
            }

            if(m->rows != 2 || m->cols != 2)
                return nullptr;

            std::vector<mpq_class>& args = m->args;
            mpq_class det = args[0]*args[3] - args[1]*args[2];
            if(det == 0){
                runtime.out << "ERROR: attempted to invert singular matrix";
                throw 1;
            }

            std::vector<mpq_class> t;
            t.push_back(args[3] / det);
            t.push_back(-args[1] / det);
            t.push_back(-args[2] / det);
            t.push_back(args[0] / det);
            for(unsigned long i = 0; i < 4; i++) t[i].canonicalize();

            return new MatrixNumeric(2, 2, t);
        }
        default:
            return nullptr;
    }
}

void Inverse::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec >= PREC_POWER){
        out << "⁜(⏴";
        e->writeMathBran(out);
        out << "⁜^⏴-1⏵⏵";
    }else{
        e->writeMathBran(out);
        out << "⁜^⏴-1⏵";
    }
}

}
