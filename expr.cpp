#include "expr.h"

#include "chelan.h"

namespace Chelan{

Expr::Expr(const ExprType& type)
    : type(type) {

}

Expr::~Expr(){
    //DO NOTHING
}

Expr* Expr::evaluateAndFree(Expr* n){
    if(Expr* m = n->evaluate()){
        delete n; //The evaluate call should delete n's children as necessary to prevent leaks
        return m;
    }else{
        return n;
    }
}

void Expr::deleteRecursive(Expr* n){
    n->deleteChildren();
    delete n;
}

Expr* Expr::remove(std::vector<Expr*>& search, const Expr* pattern, Precedence prec){
    QString p_str = pattern->getKey(prec);

    for(std::vector<Expr*>::iterator it = search.begin(); it != search.end(); it++){
        Expr* n = *it;
        if(n->getKey(prec) == p_str){
            search.erase(it);
            return n;
        }
    }

    return nullptr;
}

Expr* Expr::remove(std::vector<Expr*>& search, const Expr* pattern, const std::vector<Expr*>::iterator& end, Precedence prec){
    QString p_str = pattern->getKey(prec);
    for(auto it = search.begin(); it != end; it++){
        Expr* n = *it;
        if(n->getKey(prec) == p_str){
            search.erase(it);
            return n;
        }
    }

    return nullptr;
}

QString Expr::getKey(Precedence) const{
    return toMathBran();
}

ValueType Expr::valueType() const{
    if(type <= UNDEFINED) return SCALAR;
    else if(type <= NEGATION) return BOOLEAN;
    else if(type <= MATRIX_NUMERIC) return MATRIX;
    else if(type <= SET_ENUMERATION) return SET;
    else if(type <= UNTYPED_ADDITION) return UNTYPED;
    else return static_cast<const Read*>(this)->value_type;
}

Expr* Expr::searchForUndefined(const std::vector<Expr*>& args){
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++){
        if(args[i]->type == UNDEFINED){
            for(std::vector<Expr*>::size_type j = 0; j < i; j++) deleteRecursive(args[j]);
            for(std::vector<Expr*>::size_type j = i+1; j < args.size(); j++) deleteRecursive(args[j]);

            return args[i];
        }
    }

    return nullptr;
}

std::vector<Expr*> Expr::cloneArgs(const std::vector<Expr*> args){
    std::vector<Expr*> args_clone;
    args_clone.resize(args.size());
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        args_clone[i] = args[i]->clone();

    return args_clone;
}

bool Expr::isFalse(Expr* n){
    return n->type == BOOLEAN_VALUE && static_cast<Boolean*>(n)->value == false;
}

bool Expr::isTrue(Expr* n){
    return n->type == BOOLEAN_VALUE && static_cast<Boolean*>(n)->value == true;
}

}
