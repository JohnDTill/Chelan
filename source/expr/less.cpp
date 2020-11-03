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

Expr* Less::evaluate(Runtime& runtime){
    n = Expr::evaluateAndFree(n, runtime);

    switch(n->type){
        case PI: return new Boolean(false);
        case RATIONAL: return new Boolean(static_cast<class Rational*>(n)->value < 0);
        default: return nullptr;
    }
}

void Less::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec > PREC_LESS) out << '(';
    n->writeMathBran(out, PREC_LESS);
    out << " < 0";
    if(prec > PREC_LESS) out << ')';
}

}
