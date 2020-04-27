#include "power.h"

#include "chelan.h"

namespace AST{

Power::Power(Node* lhs, Node* rhs)
    : Node(POWER){
    this->lhs = lhs;
    this->rhs = rhs;
}

Node* Power::Raise(Node* lhs, Node* rhs){
    if(lhs->type == UNDEFINED){
        deleteRecursive(rhs);
        return lhs;
    }else if(rhs->type == UNDEFINED){
        deleteRecursive(lhs);
        return rhs;
    }else{
        return Node::evaluateAndFree(new Power(lhs, rhs));
    }
}

Node* Power::Raise(Node* lhs, mpq_class rhs){
    if(lhs->type == UNDEFINED){
        return lhs;
    }else{
        return Node::evaluateAndFree(new Power(lhs, Rational(rhs)));
    }
}

Node* Power::clone() const{
    return new Power(lhs->clone(), rhs->clone());
}

void Power::deleteChildren(){
    deleteRecursive(lhs);
    deleteRecursive(rhs);
}

Node* Power::evaluate(){
    const QString lhs_key = lhs->getKey();
    if(lhs_key == "0"){
        Node* undef = Or(IsLessThanZero(rhs->clone()), EqualsZero(rhs));

        if(undef->type == BOOLEAN){
            if(static_cast<Boolean*>(undef)->value){
                QString str= toString();
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
        return Rational(1);
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
    }

    return nullptr;
}

QString Power::toString(Node::Precedence) const{
    return lhs->toString(PREC_POWER) + '^' + rhs->toString(PREC_POWER);
}

QString Power::getKey(Node::Precedence prec) const{
    if(prec == PREC_MULTIPLICATION) return lhs->toString();
    else return toString();
}

}
