#include "equality.h"

#include "chelan.h"

namespace Chelan{

Equality::Equality(Expr* n)
    : Expr(EQUALITY),
      n(n) {}

Expr* Equality::Equals(Expr* lhs, Expr* rhs){
    if(lhs->getKey() == rhs->getKey()) return True();

    switch(lhs->type + rhs->type * num_types){
        case RATIONAL + RATIONAL*num_types:
        case PI + RATIONAL*num_types:
        case RATIONAL + PI*num_types:
            return False();
        default:
            return Expr::evaluateAndFree(new Equality( Subtract(lhs,rhs) ));
    }
}

Expr* Equality::EqualsZero(Expr* n){
    switch(n->type){
        case PI: return False();
        case RATIONAL: return new Boolean(static_cast<class Rational*>(n)->value == 0);
        default:
            return Expr::evaluateAndFree(new Equality(n));
    }
}

Expr* Equality::clone() const{
    return new Equality(n->clone());
}

Expr* Equality::evaluate(){
    return nullptr;
}

QString Equality::toMathBran(Expr::Precedence prec) const{
    QString str = n->toMathBran(PREC_EQUALITY) + " = 0";
    if(prec > PREC_EQUALITY) str.prepend('(').append(')');

    return str;
}

}
