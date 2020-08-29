#include "conjunction.h"

#include "chelan.h"

namespace Chelan{

Conjunction::Conjunction()
    : Expr(CONJUNCTION) {}

Expr* Conjunction::And(Expr* lhs, Expr* rhs){
    if(lhs->type == UNDEFINED){
        rhs->deleteChildren();
        delete rhs;

        return lhs;
    }else if(rhs->type == UNDEFINED){
        lhs->deleteChildren();
        delete lhs;

        return rhs;
    }else if(lhs->type == BOOLEAN){
        if(static_cast<Boolean*>(lhs)->value == false){
            rhs->deleteChildren();
            delete rhs;

            return lhs;
        }else{
            delete lhs;
            return rhs;
        }
    }else if(rhs->type == BOOLEAN){
        if(static_cast<Boolean*>(rhs)->value == false){
            lhs->deleteChildren();
            delete lhs;

            return rhs;
        }else{
            return lhs;
        }
    }else{
        Conjunction* n = new Conjunction();
        n->processNewArg(lhs);
        n->processNewArg(rhs);

        return Expr::evaluateAndFree(n);
    }
}

Expr* Conjunction::And(const std::vector<Expr*>& args){
    for(Expr* n : args){
        if(n->type == UNDEFINED){
            for(Expr* m : args){
                if(n!=m){
                    m->deleteChildren();
                    delete m;
                }
            }

            return n;
        }
    }

    for(Expr* n : args){
        if(n->type == BOOLEAN && static_cast<Boolean*>(n)->value == false){
            for(Expr* m : args){
                if(n!=m){
                    m->deleteChildren();
                    delete m;
                }
            }

            return n;
        }
    }

    Conjunction* a = new Conjunction();
    for(Expr* n : args) a->processNewArg(n);

    return Expr::evaluateAndFree(a);
}

void Conjunction::processNewArg(Expr* n){
    if(n->type == BOOLEAN){
        Q_ASSERT(static_cast<Boolean*>(n)->value);
        delete n;
    }else if(n->type == CONJUNCTION){
        flatten(static_cast<Conjunction*>(n));
    }else{
        insertOrDiscard(n);
    }
}

Expr* Conjunction::clone() const{
    Conjunction* n = new Conjunction();
    n->args.resize(args.size());
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        n->args[i] = args[i]->clone();

    return n;
}

void Conjunction::deleteChildren(){
    for(Expr* n : args){
        n->deleteChildren();
        delete n;
    }
}

Expr* Conjunction::evaluate(){
    if(args.size() == 0) return new Boolean(true); //Only true values were present
    if(args.size() == 1) return *args.begin();

    std::sort(args.begin(), args.end(), compare);
    setKey();

    for(auto it = args.begin(); it < args.end(); it++){
        // Reach disjunctive normal form by distributing disjunctions
        // A ∧ B ∧ (C ∨ D ∨ E)  ⇒  A ∧ B ∧ C  ∨
        //                         A ∧ B ∧ D  ∨
        //                         A ∧ B ∧ E

        Expr* n = *it;
        if(n->type == DISJUNCTION){
            args.erase(it);
            Disjunction* old_disjunction = static_cast<Disjunction*>(n);
            std::vector<Expr*> new_disjunction_args;
            for(Expr* old_disjunction_arg : old_disjunction->args){
                std::vector<Expr*> new_conjunction_args = args;
                args.push_back(old_disjunction_arg);

                new_disjunction_args.push_back( And(new_conjunction_args) );
                //This will work recursively for multiple disjunctions
            }

            return Or(new_disjunction_args);
        }
    }

    return nullptr;
}

QString Conjunction::toMathBran(Expr::Precedence prec) const{
    QString str = key;
    if(prec > PREC_CONJUNCTION) str.prepend('(').append(')');

    return str;
}

void Conjunction::flatten(Conjunction* c){
    for(Expr* n : c->args) insertOrDiscard(n);
    delete c;
}

void Conjunction::insertOrDiscard(Expr* n){
    QString key = n->getKey();
    for(Expr* a : args){
        if(a->getKey() == key){
            n->deleteChildren();
            delete n;

            return;
        }
    }

    args.push_back(n);
}

void Conjunction::setKey(){
    key = args[0]->toMathBran(PREC_CONJUNCTION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        key += " ∧ " + args[i]->toMathBran(PREC_CONJUNCTION);
}

bool Conjunction::compare(const Expr* a, const Expr* b){
    return a->getKey() < b->getKey();
}

}
