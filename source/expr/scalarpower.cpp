#include "scalarpower.h"

#include "chelan.h"

namespace Chelan{

ScalarPower::ScalarPower(Expr* lhs, Expr* rhs)
    : Expr(SCALAR_POWER), lhs(lhs), rhs(rhs){}

Expr* ScalarPower::clone() const{
    return new ScalarPower(lhs->clone(), rhs->clone());
}

void ScalarPower::deleteChildren(){
    deleteRecursive(lhs);
    deleteRecursive(rhs);
}

Expr* ScalarPower::evaluate(Runtime& runtime){
    lhs = evaluateAndFree(lhs, runtime);
    rhs = evaluateAndFree(rhs, runtime);

    if(lhs->type == RATIONAL && rhs->type == RATIONAL){
        Rational* lhs_rat = static_cast<Rational*>(lhs);
        Rational* rhs_rat = static_cast<Rational*>(rhs);

        if( rhs_rat->value.get_den() != 1 ||
            rhs_rat->value.get_num() > std::numeric_limits<unsigned long>::max() ) return nullptr;

        if( rhs_rat->value == 0){
            delete rhs;
            delete lhs;
            return new Rational(1);
        }else if( rhs_rat->value == 1 ){
            delete rhs;
            return lhs;
        }else if( rhs_rat->value == -1 ){
            Rational* recip = new Rational(1 / lhs_rat->value);
            delete rhs;
            delete lhs;
            return recip;
        }else if(lhs_rat->value.get_num() > std::numeric_limits<unsigned long>::max() ||
                 lhs_rat->value.get_den() > std::numeric_limits<unsigned long>::max() ){
            return nullptr;
        }

        auto num = lhs_rat->value.get_num().get_ui();
        auto den = lhs_rat->value.get_den().get_ui();
        auto rv = rhs_rat->value.get_num().get_ui();
        mpz_t num_exp, den_exp;
        mpz_init(num_exp);
        mpz_init(den_exp);
        mpz_ui_pow_ui(num_exp, num, rv);
        mpz_ui_pow_ui(den_exp, den, rv);

        mpq_class result = rhs_rat->value >= 0 ?
                           mpq_class(mpz_class(num_exp), mpz_class(den_exp)) :
                           mpq_class(mpz_class(den_exp), mpz_class(num_exp));
        if(lhs_rat->value < 0 && rv%2) result *= -1;

        delete lhs;
        delete rhs;
        return new Rational(result);
    }

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

    return nullptr;
}

void ScalarPower::writeMathBran(QTextStream& out, Precedence) const{
    lhs->writeMathBran(out, PREC_POWER);
    out << "⁜^⏴";
    rhs->writeMathBran(out);
    out << "⏵";
}

QString ScalarPower::getKey(Precedence prec) const{
    if(prec == PREC_MULTIPLICATION) return lhs->getKey(PREC_MULTIPLICATION);
    else return toMathBran();
}

}
