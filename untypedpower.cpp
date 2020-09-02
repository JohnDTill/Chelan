#include "untypedpower.h"

#include "chelan.h"

namespace Chelan {

UntypedPower::UntypedPower(Expr* lhs, Expr* rhs)
    : Expr(UNTYPED_POWER), lhs(lhs), rhs(rhs) {

}

Expr* UntypedPower::clone() const{
    return new UntypedPower(lhs->clone(), rhs->clone());
}

void UntypedPower::deleteChildren(){
    Expr::deleteRecursive(lhs);
    Expr::deleteRecursive(rhs);
}

Expr* UntypedPower::evaluate(){
    return nullptr;
}

QString UntypedPower::toMathBran(Expr::Precedence) const{
    return lhs->toMathBran(PREC_POWER) + "⁜^⏴" + rhs->toMathBran() + "⏵";
}

void UntypedPower::visitChildren(Interpreter* interpreter){
    lhs = interpreter->evaluate(lhs);
    rhs = interpreter->evaluate(rhs);
}

Expr* UntypedPower::evaluate(QString& err_msg){
    if(lhs->valueType() == SCALAR && rhs->valueType() == SCALAR){
        return ScalarPower::Raise(lhs, rhs);
    }else{
        return nullptr;
    }
}

}
