#include "negation.h"

#include "chelan.h"

namespace Chelan{

Negation::Negation(Expr* n)
    : Expr(NEGATION),
      n(n) {}

Expr* Negation::Not(Expr* n){
    switch(n->type){
        case UNDEFINED: return n;
        case BOOLEAN_VALUE:{
            Expr* inverse = new Boolean(!static_cast<Boolean*>(n)->value);
            delete n;
            return inverse;
        }
        case NEGATION:{ //¬¬A ⇒ A (disjunctive normal form, double negation)
            Expr* child = static_cast<Negation*>(n)->n;
            delete n;

            return child;
        }
        case CONJUNCTION:{ //¬(A ∧ B) ⇒ ¬A ∨ ¬B  (disjunctive normal form, De Morgan)
            std::vector<Expr*> negations;
            for(Expr* a : static_cast<Conjunction*>(n)->args)
                negations.push_back(Not(a));
            delete n;

            return Disjunction::Or(negations);
        }
        case DISJUNCTION:{ //¬(A ∨ B) ⇔ ¬A ∧ ¬B  (disjunctive normal form, De Morgan))
            std::vector<Expr*> negations;
            for(Expr* a : static_cast<Disjunction*>(n)->args)
                negations.push_back(Not(a));
            delete n;

            return Conjunction::And(negations);
        }
        default:
            return Expr::evaluateAndFree(new Negation(n));
    }
}

Expr* Negation::clone() const{
    return new Negation(n);
}

void Negation::deleteChildren(){
    n->deleteChildren();
    delete n;
}

Expr* Negation::evaluate(){
    return nullptr;
}

QString Negation::toMathBran(Expr::Precedence prec) const{
    QString str = "¬" + n->toMathBran(PREC_NEGATION);
    if(prec > PREC_NEGATION) str.prepend('(').append(')');

    return str;
}

void Negation::visitChildren(Interpreter* interpreter){
    n = interpreter->evaluate(n);
}

}
