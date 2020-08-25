#include "equality.h"

#include "chelan.h"

namespace AST{

Equality::Equality(Node* n)
    : Node(EQUALITY),
      n(n) {}

Node* Equality::Equals(Node* lhs, Node* rhs){
    if(lhs->getKey() == rhs->getKey()) return True();

    switch(lhs->type + rhs->type * num_types){
        case RATIONAL + RATIONAL*num_types:
        case PI + RATIONAL*num_types:
        case RATIONAL + PI*num_types:
            return False();
        default:
            return Node::evaluateAndFree(new Equality( Subtract(lhs,rhs) ));
    }
}

Node* Equality::EqualsZero(Node* n){
    switch(n->type){
        case PI: return False();
        case RATIONAL: return new Boolean(static_cast<class Rational*>(n)->value == 0);
        default:
            return Node::evaluateAndFree(new Equality(n));
    }
}

Node* Equality::clone() const{
    return new Equality(n->clone());
}

Node* Equality::evaluate(){
    return nullptr;
}

QString Equality::toMathBran(Node::Precedence prec) const{
    QString str = n->toMathBran(PREC_EQUALITY) + " = 0";
    if(prec > PREC_EQUALITY) str.prepend('(').append(')');

    return str;
}

}
