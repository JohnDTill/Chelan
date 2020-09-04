#include "scalaraddition.h"

#include "chelan.h"

namespace Chelan{

ScalarAddition::ScalarAddition(const std::vector<Expr*>& args)
    : Expr(SCALAR_ADDITION, SCALAR), args(args), constant(0){}

ScalarAddition::ScalarAddition(Expr* lhs, mpq_class rhs)
    : Expr(SCALAR_ADDITION, SCALAR), args({lhs}), constant(rhs){}

ScalarAddition::ScalarAddition(mpq_class lhs, Expr* rhs)
    : Expr(SCALAR_ADDITION, SCALAR), args({rhs}), constant(lhs){}

Expr* ScalarAddition::Subtract(Expr* lhs, Expr* rhs){
    return new ScalarAddition({lhs, new ScalarMultiplication(-1, rhs)});
}

Expr* ScalarAddition::clone() const{
    ScalarAddition* cl = new ScalarAddition(cloneArgs(args));
    cl->key = key;
    return cl;
}

void ScalarAddition::deleteChildren(){
    for(Expr* n : args){
        n->deleteChildren();
        delete n;
    }
}

Expr* ScalarAddition::evaluate(){
    //Fast path//
    foldConstants();
    if(args.size()==0){
        constant.canonicalize();
        return new Rational(constant);
    }

    //Symbolic//
    if(Expr* n = searchForUndefined(args)) return n;

    flatten();
    collect();

    constant.canonicalize();
    if(args.size()==0) return new Rational(constant);
    else if(args.size()==1 && constant==0) return *args.begin();

    setKey();
    return nullptr;
}

QString ScalarAddition::toMathBran(Precedence prec) const{
    QString str = key;
    if(prec > PREC_ADDITION) str.prepend('(').append(')');

    return str;
}

void ScalarAddition::visitChildren(Interpreter* interpreter){
    for(vInt i = 0; i < args.size(); i++)
        args[i] = interpreter->evaluate(args[i]);
}

void ScalarAddition::foldConstants(){
    for(vInt i = args.size()-1; i < vInt_MAX; i--){
        if(args[i]->type == RATIONAL){
            constant += static_cast<class Rational*>(args[i])->value;
            delete args[i];
            args.erase(args.begin()+i);
        }
    }
}

void ScalarAddition::flatten(){
    if(args.empty()) return;

    std::vector<Expr*> new_args;
    for(vInt i = args.size()-1; i < vInt_MAX; i--){
        if(args[i]->type == SCALAR_ADDITION){
            flatten(static_cast<ScalarAddition*>(args[i]), new_args);
            delete args[i];
            args.erase(args.begin()+i);
        }
    }

    for(Expr* n : new_args) args.push_back(n);
}

void ScalarAddition::flatten(ScalarAddition* a, std::vector<Expr*>& new_args){
    constant += a->constant;
    for(Expr* n : a->args) new_args.push_back(n);
}

void ScalarAddition::collect(){
    if(args.size() < 2) return;

    std::sort(args.begin(), args.end(), compare<PREC_ADDITION>);

    vInt pattern_end = args.size() - 1;
    QString search_key = args.back()->getKey(PREC_ADDITION);
    vInt i;
    for(i = pattern_end; i < vInt_MAX; i--){
        QString target_key = args[i]->getKey(PREC_ADDITION);

        if(target_key != search_key){
            if(pattern_end - i > 1) collect(i+1, pattern_end);
            search_key = target_key;
            pattern_end = i;
        }
    }

    if(pattern_end - i > 1) collect(0, pattern_end);
}

void ScalarAddition::collect(vInt start, vInt end){
    mpq_class factor = 0;
    Expr* n = args[start]->clone();
    if(n->type == SCALAR_MULTIPLICATION)
        static_cast<ScalarMultiplication*>(n)->constant = 1;


    for(vInt i = end; i >= start && i < vInt_MAX; i--){
        if(args[i]->type == SCALAR_MULTIPLICATION){
            factor += static_cast<ScalarMultiplication*>(args[i])->constant;
        }else{
            factor++;
        }
        deleteRecursive(args[i]);
    }

    Expr* factored = new ScalarMultiplication(factor, n);
    if(factored->type != RATIONAL){
        args[start] = factored;
        args.erase(args.begin()+start+1, args.begin()+end+1);
    }else{
        deleteRecursive(factored);
        args.erase(args.begin()+start, args.begin()+end+1);
    }
}

void ScalarAddition::setKey(){
    std::sort(args.begin(), args.end(), compare<PREC_ADDITION>);

    if(constant!=0) key = QString::fromStdString(constant.get_str()) + " + ";
    else key = "";
    key += args[0]->toMathBran(PREC_ADDITION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        key += " + " + args[i]->toMathBran(PREC_ADDITION);
}

}
