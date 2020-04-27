#include "negation.h"

#include "chelan.h"

namespace AST{

Negation::Negation(Node* n)
    : Node(NEGATION),
      n(n) {}

Node* Negation::Not(Node* n){
    switch(n->type){
        case UNDEFINED: return n;
        case BOOLEAN:{
            Node* inverse = new Boolean(!static_cast<Boolean*>(n)->value);
            delete n;
            return inverse;
        }
        case NEGATION:{ //¬¬A ⇒ A (disjunctive normal form, double negation)
            Node* child = static_cast<Negation*>(n)->n;
            delete n;

            return child;
        }
        case CONJUNCTION:{ //¬(A ∧ B) ⇒ ¬A ∨ ¬B  (disjunctive normal form, De Morgan)
            std::vector<Node*> negations;
            for(Node* a : static_cast<Conjunction*>(n)->args)
                negations.push_back(Not(a));
            delete n;

            return Or(negations);
        }
        case DISJUNCTION:{ //¬(A ∨ B) ⇔ ¬A ∧ ¬B  (disjunctive normal form, De Morgan))
            std::vector<Node*> negations;
            for(Node* a : static_cast<Disjunction*>(n)->args)
                negations.push_back(Not(a));
            delete n;

            return And(negations);
        }
        default:
            return Node::evaluateAndFree(new Negation(n));
    }
}

Node* Negation::clone() const{
    return new Negation(n);
}

void Negation::deleteChildren(){
    n->deleteChildren();
    delete n;
}

Node* Negation::evaluate(){
    return nullptr;
}

QString Negation::toString(Node::Precedence prec) const{
    QString str = "¬" + n->toString(PREC_NEGATION);
    if(prec > PREC_NEGATION) str.prepend('(').append(')');

    return str;
}

}
