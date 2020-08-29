#include "less.h"

#include "chelan.h"

namespace Chelan{

Less::Less(Expr* n)
    : Expr(LESS),
      n(n) {}

Expr* Less::IsLess(Expr* lhs, Expr* rhs){
    if(lhs->getKey() == rhs->getKey()) return False();

    switch(lhs->type + rhs->type * num_types){
        case RATIONAL + RATIONAL*num_types:
            return new Boolean(
                        static_cast<class Rational*>(lhs)->value < static_cast<class Rational*>(rhs)->value
                        );
        default:
            return Expr::evaluateAndFree(new class Less( Subtract(lhs,rhs) ));
    }
}

Expr* Less::IsLessThanZero(Expr* n){
    switch(n->type){
        case PI: return False();
        case RATIONAL: return new Boolean(static_cast<class Rational*>(n)->value < 0);
        default:
            return Expr::evaluateAndFree(new class Less(n));
    }
}

Expr* Less::clone() const{
    return new Less(n->clone());
}

Expr* Less::evaluate(){
    return nullptr;
}

QString Less::toMathBran(Expr::Precedence prec) const{
    QString str = n->toMathBran(PREC_LESS) + " < 0";
    if(prec > PREC_LESS) str.prepend('(').append(')');

    return str;
}

}
