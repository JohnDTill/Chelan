#include "scalarmultiplication.h"

#include "chelan.h"

namespace Chelan{

ScalarMultiplication::ScalarMultiplication(const std::vector<Expr*>& args)
    : Expr(SCALAR_MULTIPLICATION),
      args(args) {}

Expr* ScalarMultiplication::Multiply(Expr* lhs, Expr* rhs){
    return Expr::evaluateAndFree(new ScalarMultiplication({lhs, rhs}));
}

Expr* ScalarMultiplication::Multiply(mpq_class lhs, Expr* rhs){
    ScalarMultiplication* m = new ScalarMultiplication({rhs});
    m->constant = lhs;

    return Expr::evaluateAndFree(m);
}

Expr* ScalarMultiplication::Multiply(const std::vector<Expr*>& args){
    return Expr::evaluateAndFree(new ScalarMultiplication(args));
}

Expr* ScalarMultiplication::Divide(Expr* lhs, Expr* rhs){
    return Multiply(lhs, ScalarPower::Raise(rhs, -1));
}

Expr* ScalarMultiplication::clone() const{
    ScalarMultiplication* cl = new ScalarMultiplication(cloneArgs(args));
    cl->key = key;
    return cl;
}

void ScalarMultiplication::deleteChildren(){
    for(Expr* n : args){
        n->deleteChildren();
        delete n;
    }
}

Expr* ScalarMultiplication::evaluate(){
    if(Expr* n = searchForUndefined(args)) return n;

    foldConstants();
    flatten();
    collect();

    constant.canonicalize();

    if(args.size()==0){
        return new Rational(constant);
    }else if(constant == 0){
        //DO THIS: 0*x => 0 only if x is defined
        //if(IsDefined(args))...
        deleteChildren();
        return new Rational(constant);
    }else if(args.size()==1 && constant==1){
        return *args.begin();
    }

    setKey();

    return nullptr;
}

QString ScalarMultiplication::toMathBran(Precedence prec) const{
    QString str = key;
    if(constant!=1){
        if(constant==-1) str.prepend('-');
        else if(constant.get_den()==1) str.prepend(QString::fromStdString(constant.get_str()));
        else str.prepend("⁜f⏴" + QString::fromStdString(constant.get_num().get_str()) + "⏵⏴"
                         + QString::fromStdString(constant.get_den().get_str()) + "⏵");
    }
    if(prec > PREC_MULTIPLICATION) str.prepend('(').append(')');

    return str;
}

void ScalarMultiplication::visitChildren(Interpreter* interpreter){
    for(Expr* expr : args) expr = interpreter->evaluate(expr);
}

void ScalarMultiplication::foldConstants(){
    for(int i = args.size()-1; i >= 0; i--){
        if(args[i]->type == RATIONAL){
            constant *= static_cast<class Rational*>(args[i])->value;
            delete args[i];
            args.erase(args.begin()+i);
        }
    }
}

void ScalarMultiplication::flatten(){
    if(args.empty()) return;

    std::vector<Expr*> new_args;
    for(int i = args.size()-1; i >= 0; i--){
        if(args[i]->type == SCALAR_MULTIPLICATION){
            flatten(static_cast<ScalarMultiplication*>(args[i]), new_args);
            delete args[i];
            args.erase(args.begin()+i);
        }
    }

    for(Expr* n : new_args) args.push_back(n);
}

void ScalarMultiplication::flatten(ScalarMultiplication* a, std::vector<Expr*>& new_args){
    constant *= a->constant;
    for(Expr* n : a->args) new_args.push_back(n);
}

void ScalarMultiplication::collect(){
    if(args.size() < 2) return;

    std::sort(args.begin(), args.end(), compare<PREC_MULTIPLICATION>);

    int pattern_end = args.size() - 1;
    QString search_key = args.back()->getKey(PREC_MULTIPLICATION);
    int i;
    for(int i = pattern_end; i >= 0; i--){
        QString target_key = args[i]->getKey(PREC_MULTIPLICATION);

        if(target_key != search_key){
            if(pattern_end - i > 1) collect(i+1, pattern_end);
            search_key = target_key;
            pattern_end = i;
        }
    }

    if(pattern_end - i > 1) collect(0, pattern_end);
}

void ScalarMultiplication::collect(int start, int end){
    std::vector<Expr*> factors;
    std::vector<Expr*> factors_positive;
    Expr* n = args[start]->clone();
    if(n->type == SCALAR_POWER){
        ScalarPower* p = static_cast<ScalarPower*>(n);
        deleteRecursive(p->rhs);
        n = p->lhs;
        delete p;
    }
    if(n->type == SCALAR_MULTIPLICATION){
        static_cast<ScalarMultiplication*>(n)->constant = 1;
    }

    for(int i = end; i >= start; i--){
        if(args[i]->type == SCALAR_POWER){
            ScalarPower* p = static_cast<ScalarPower*>(args[i]);
            factors.push_back(p->rhs);
            if(p->lhs->type == SCALAR_MULTIPLICATION){
                n = Multiply(static_cast<ScalarMultiplication*>(p->lhs)->constant, n);
            }
            deleteRecursive(p->lhs);
            delete p;
        }else{
            factors.push_back(new Rational(1));
            if(args[i]->type == SCALAR_MULTIPLICATION){
                n = Multiply(static_cast<ScalarMultiplication*>(args[i])->constant, n);
            }
            deleteRecursive(args[i]);
        }
    }
    args.erase(args.begin()+start+1, args.begin()+end+1);

    Expr* zero_base = Equality::EqualsZero(n->clone());

    for(Expr* n : factors){
        Expr* exponent_is_positive =
            Negation::Not(
                Disjunction::Or(
                    Less::IsLessThanZero(n->clone()),
                    Equality::EqualsZero(n->clone())
                )
            );
        factors_positive.push_back( exponent_is_positive );
    }

    Expr* factored_exponent = ScalarPower::Raise(n, ScalarAddition::Add(factors));
    Expr* positive_exponents = Conjunction::And(factors_positive);
    Expr* is_defined = Disjunction::Or(Negation::Not(zero_base), positive_exponents);

    Expr* cv = ConditionalValue::Ternary(
                   is_defined,
                   factored_exponent,
                   new Undefined("Divide by 0")
               );
    args[start] = cv;
}

void ScalarMultiplication::setKey(){
    std::sort(args.begin(), args.end(), compare<PREC_MULTIPLICATION>);
    key = args[0]->toMathBran(PREC_ADDITION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        key += ' ' + args[i]->toMathBran(PREC_ADDITION);
}

QString ScalarMultiplication::getKey(Expr::Precedence prec) const{
    return (prec == PREC_ADDITION || prec == PREC_MULTIPLICATION) ? key : toMathBran();
}

}
