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

void Equality::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec > PREC_EQUALITY) out << '(';
    n->writeMathBran(out, PREC_EQUALITY);
    out << " = 0";
    if(prec > PREC_EQUALITY) out << ')';
}

}
