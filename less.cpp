#include "less.h"

#include "chelan.h"

namespace AST{

Less::Less(Node* n)
    : Node(LESS),
      n(n) {}

Node* Less::IsLess(Node* lhs, Node* rhs){
    if(lhs->getKey() == rhs->getKey()) return False();

    switch(lhs->type + rhs->type * num_types){
        case RATIONAL + RATIONAL*num_types:
            return new Boolean(
                        static_cast<class Rational*>(lhs)->value < static_cast<class Rational*>(rhs)->value
                        );
        default:
            return Node::evaluateAndFree(new class Less( Subtract(lhs,rhs) ));
    }
}

Node* Less::IsLessThanZero(Node* n){
    switch(n->type){
        case PI: return False();
        case RATIONAL: return new Boolean(static_cast<class Rational*>(n)->value < 0);
        default:
            return Node::evaluateAndFree(new class Less(n));
    }
}

Node* Less::clone() const{
    return new Less(n->clone());
}

Node* Less::evaluate(){
    return nullptr;
}

QString Less::toMathBran(Node::Precedence prec) const{
    QString str = n->toMathBran(PREC_LESS) + " < 0";
    if(prec > PREC_LESS) str.prepend('(').append(')');

    return str;
}

}
