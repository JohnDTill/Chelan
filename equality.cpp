#include "equality.h"

#include "chelan.h"

namespace Chelan{

Equality::Equality(Expr* n)
    : Expr(EQUALITY), n(n) {}

Expr* Equality::Equals(Expr* lhs, Expr* rhs){
    Expr* diff = lhs->toMathBran() < rhs->toMathBran() ?
                 ScalarAddition::Subtract(lhs,rhs) :
                 ScalarAddition::Subtract(rhs,lhs);

    return new Equality(diff);
}

Expr* Equality::clone() const{
    return new Equality(n->clone());
}

Expr* Equality::evaluate(){
    switch(n->type){
        case PI: return new Boolean(false);
        case RATIONAL: return new Boolean(static_cast<class Rational*>(n)->value == 0);
        default: return nullptr;
    }
}

QString Equality::toMathBran(Precedence prec) const{
    QString str = n->toMathBran(PREC_EQUALITY) + " = 0";
    if(prec > PREC_EQUALITY) str.prepend('(').append(')');

    return str;
}

}
