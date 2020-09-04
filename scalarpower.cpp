#include "scalarpower.h"

#include "chelan.h"

namespace Chelan{

ScalarPower::ScalarPower(Expr* lhs, Expr* rhs)
    : Expr(SCALAR_POWER, SCALAR), lhs(lhs), rhs(rhs){}

Expr* ScalarPower::clone() const{
    return new ScalarPower(lhs->clone(), rhs->clone());
}

void ScalarPower::deleteChildren(){
    deleteRecursive(lhs);
    deleteRecursive(rhs);
}

Expr* ScalarPower::evaluate(){
    if(lhs->type == UNDEFINED){
        deleteRecursive(rhs);
        return lhs;
    }else if(rhs->type == UNDEFINED){
        deleteRecursive(lhs);
        return rhs;
    }

    const QString lhs_key = lhs->getKey();
    if(lhs_key == "0"){
        Expr* undef = new Disjunction({new Less(rhs->clone()), new Equality(rhs)});

        if(undef->type == BOOLEAN_VALUE){
            if(static_cast<Boolean*>(undef)->value){
                QString str= toMathBran();
                delete lhs;

                return new Undefined("Division by zero: " + str);
            }else{
                return lhs;
            }
        }else{
            return new ConditionalValue(undef, new Undefined("Division by zero"), lhs);
        }
    }

    const QString rhs_key = rhs->getKey();
    if(rhs_key == "0"){
        deleteChildren();
        return new Rational(1);
    }else if(rhs_key == "1"){
        delete rhs;
        return lhs;
    }

    if(lhs->type == RATIONAL && rhs->type == RATIONAL){
        //const mpq_class& vL = static_cast<class Rational*>(lhs)->value;
        //const mpq_class& vR = static_cast<class Rational*>(rhs)->value;

        //DO THIS:
        // complete the calculation
        // need some metric for when the result is too large

        mpq_class lv = static_cast<class Rational*>(lhs)->value;
        mpq_class rv = static_cast<class Rational*>(rhs)->value;

        if(rv == -1) return new class Rational(1/lv);
    }

    return nullptr;
}

QString ScalarPower::toMathBran(Expr::Precedence) const{
    return lhs->toMathBran(PREC_POWER) + "⁜^⏴" + rhs->toMathBran(PREC_NONE) + "⏵";
}

void ScalarPower::visitChildren(Interpreter* interpreter){
    lhs = interpreter->evaluate(lhs);
    rhs = interpreter->evaluate(rhs);
}

QString ScalarPower::getKey(Expr::Precedence prec) const{
    if(prec == PREC_MULTIPLICATION) return lhs->getKey(PREC_MULTIPLICATION);
    else return toMathBran();
}

}
