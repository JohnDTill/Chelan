#include "transpose.h"

#include <chelan.h>

namespace Chelan {

Transpose::Transpose(Expr* e)
    : Expr(TRANSPOSE), e(e) {}

Expr* Transpose::clone() const{
    return new Transpose(e);
}

void Transpose::deleteChildren(){
    e->deleteChildren();
    delete e;
}

Expr* Transpose::evaluate(Runtime& runtime){
    e = Expr::evaluateAndFree(e, runtime);

    switch (e->type) {
        case MATRIX_NUMERIC:{
            MatrixNumeric* m = static_cast<MatrixNumeric*>(e);
            std::vector<mpq_class> t(m->rows*m->cols);
            for(unsigned long i = 0; i < m->rows; i++)
                for(unsigned long j = 0; j < m->cols; j++)
                    t[i + j*m->rows] = m->args[j + i*m->cols];
            return new MatrixNumeric(m->cols, m->rows, t);
        }
        default:
            return nullptr;
    }
}

void Transpose::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec >= PREC_POWER){
        out << "⁜(⏴";
        e->writeMathBran(out);
        out << "⁜^⏴⊤⏵⏵";
    }else{
        e->writeMathBran(out);
        out << "⁜^⏴⊤⏵";
    }
}

}
