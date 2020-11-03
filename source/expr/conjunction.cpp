#include "conjunction.h"

#include "chelan.h"

namespace Chelan{

Conjunction::Conjunction(const std::vector<Expr*>& args)
    : Expr(CONJUNCTION), args(args) {}

Expr* Conjunction::clone() const{
    return new Conjunction(cloneArgs(args));
}

void Conjunction::deleteChildren(){
    for(Expr* n : args){
        n->deleteChildren();
        delete n;
    }
}

Expr* Conjunction::evaluate(Runtime& runtime){
    evaluateAndFreeArgs(args, runtime);

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
        if(n->type == BOOLEAN_VALUE && static_cast<Boolean*>(n)->value == false){
            for(Expr* m : args){
                if(n!=m){
                    m->deleteChildren();
                    delete m;
                }
            }

            return n;
        }
    }

    for(std::vector<Expr*>::size_type i = args.size()-1; i < args.size(); i--){
        if(args[i]->type == BOOLEAN_VALUE){
            Q_ASSERT(static_cast<Boolean*>(args[i])->value);
            delete args[i];
            args.erase(args.begin() + i);
        }else if(args[i]->type == CONJUNCTION){
            flatten(static_cast<Conjunction*>(args[i]));
        }
    }

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

                new_disjunction_args.push_back( new Conjunction(new_conjunction_args) );
                //This will work recursively for multiple disjunctions
            }

            return new Disjunction(new_disjunction_args);
        }
    }

    return nullptr;
}

void Conjunction::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec > PREC_CONJUNCTION) out << '(' << key << ')';
    else out << key;
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
