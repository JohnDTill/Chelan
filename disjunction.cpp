#include "disjunction.h"

#include "chelan.h"

namespace Chelan{

Disjunction::Disjunction(const std::vector<Expr*>& args)
    : Expr(DISJUNCTION), args(args) {}

Expr* Disjunction::clone() const{
    return new Disjunction(cloneArgs(args));
}

void Disjunction::deleteChildren(){
    for(Expr* n : args){
        n->deleteChildren();
        delete n;
    }
}

Expr* Disjunction::evaluate(){
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
        if(n->type == BOOLEAN_VALUE && static_cast<Boolean*>(n)->value == true){
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
            Q_ASSERT(static_cast<Boolean*>(args[i])->value == false);
            delete args[i];
            args.erase(args.begin() + i);
        }else if(args[i]->type == DISJUNCTION){
            flatten(static_cast<Disjunction*>(args[i]));
        }
    }

    if(args.size() == 0) return new Boolean(false); //Only false values were inserted
    if(args.size() == 1) return *args.begin();

    std::sort(args.begin(), args.end(), compare);
    setKey();

    return nullptr;
}

void Disjunction::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec > PREC_DISJUNCTION) out << '(' << key << ')';
    else out << key;
}

void Disjunction::flatten(Disjunction* d){
    for(Expr* n : d->args) insertOrDiscard(n);
    delete d;
}

void Disjunction::insertOrDiscard(Expr* n){
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

void Disjunction::setKey(){
    key = args[0]->toMathBran(PREC_DISJUNCTION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        key += " ∨ " + args[i]->toMathBran(PREC_DISJUNCTION);
}

bool Disjunction::compare(const Expr* a, const Expr* b){
    return a->getKey() < b->getKey();
}

}
