#include "less.h"

#include "chelan.h"

namespace Chelan{

Less::Less(Expr* n)
    : Expr(LESS), n(n) {}

Expr* Less::IsLess(Expr* lhs, Expr* rhs){
    return new Less(ScalarAddition::Subtract(lhs, rhs));
}

Expr* Less::clone() const{
    return new Less(n->clone());
}

Expr* Less::evaluate(){
    switch(n->type){
        case PI: return new Boolean(false);
        case RATIONAL: return new Boolean(static_cast<class Rational*>(n)->value < 0);
        default: return nullptr;
    }
}

QString Less::toMathBran(Precedence prec) const{
    QString str = n->toMathBran(PREC_LESS) + " < 0";
    if(prec > PREC_LESS) str.prepend('(').append(')');

    return str;
}

}
