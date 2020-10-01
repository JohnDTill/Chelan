#include "read.h"

namespace Chelan {

Read::Read(Expr*& var)
    : Expr(READ), var(var) {}

Expr* Read::clone() const{
    return new Read(var);
}

Expr* Read::evaluate(){
    return Expr::evaluateAndFree(var->clone());
}

QString Read::toMathBran(Precedence) const{
    return "⚠r(" + var->toMathBran() + ")";
}

}
