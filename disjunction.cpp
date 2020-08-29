#include "disjunction.h"

#include "chelan.h"

namespace Chelan{

Disjunction::Disjunction()
    : Expr(DISJUNCTION) {}

Expr* Disjunction::Or(Expr* lhs, Expr* rhs){
    if(lhs->type == UNDEFINED){
        rhs->deleteChildren();
        delete rhs;

        return lhs;
    }else if(rhs->type == UNDEFINED){
        lhs->deleteChildren();
        delete lhs;

        return rhs;
    }else if(lhs->type == BOOLEAN){
        if(static_cast<Boolean*>(lhs)->value == true){
            rhs->deleteChildren();
            delete rhs;

            return lhs;
        }else{
            delete lhs;
            return rhs;
        }
    }else if(rhs->type == BOOLEAN){
        if(static_cast<Boolean*>(rhs)->value == true){
            lhs->deleteChildren();
            delete lhs;

            return rhs;
        }else{
            return lhs;
        }
    }else{
        Disjunction* n = new Disjunction();
        n->processNewArg(lhs);
        n->processNewArg(rhs);

        return Expr::evaluateAndFree(n);
    }
}

Expr* Disjunction::Or(const std::vector<Expr*>& args){
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
        if(n->type == BOOLEAN && static_cast<Boolean*>(n)->value == true){
            for(Expr* m : args){
                if(n!=m){
                    m->deleteChildren();
                    delete m;
                }
            }

            return n;
        }
    }

    Disjunction* a = new Disjunction();
    for(Expr* n : args) a->processNewArg(n);

    return Expr::evaluateAndFree(a);
}

void Disjunction::processNewArg(Expr* n){
    if(n->type == BOOLEAN){
        //Q_ASSERT(static_cast<Boolean*>(n)->value == false);
        delete n;
    }else if(n->type == DISJUNCTION){
        flatten(static_cast<Disjunction*>(n));
    }else{
        insertOrDiscard(n);
    }
}

Expr* Disjunction::clone() const{
    Disjunction* n = new Disjunction();
    n->args.resize(args.size());
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        n->args[i] = args[i]->clone();

    return n;
}

void Disjunction::deleteChildren(){
    for(Expr* n : args){
        n->deleteChildren();
        delete n;
    }
}

Expr* Disjunction::evaluate(){
    if(args.size() == 0) return new Boolean(false); //Only false values were inserted
    if(args.size() == 1) return *args.begin();

    std::sort(args.begin(), args.end(), compare);
    setKey();

    return nullptr;
}

QString Disjunction::toMathBran(Expr::Precedence prec) const{
    QString str = key;
    if(prec > PREC_DISJUNCTION) str.prepend('(').append(')');

    return str;
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
