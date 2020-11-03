#include "scalarmultiplication.h"

#include "chelan.h"

namespace Chelan{

ScalarMultiplication::ScalarMultiplication(const std::vector<Expr*>& args)
    : Expr(SCALAR_MULTIPLICATION), args(args), constant(1) {}

ScalarMultiplication::ScalarMultiplication(Expr* lhs, mpq_class rhs)
    : Expr(SCALAR_MULTIPLICATION), args({lhs}), constant(rhs){}

ScalarMultiplication::ScalarMultiplication(mpq_class lhs, Expr* rhs)
    : Expr(SCALAR_MULTIPLICATION), args({rhs}), constant(lhs){}

Expr* ScalarMultiplication::Divide(Expr* lhs, Expr* rhs){
    return new ScalarMultiplication({lhs, new ScalarPower(rhs, new Rational(-1))});
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

Expr* ScalarMultiplication::evaluate(Runtime& runtime){
    evaluateAndFreeArgs(args, runtime);

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

void ScalarMultiplication::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec > PREC_MULTIPLICATION) out << '(';
    if(constant!=1){
        if(constant==-1) out << '-' << key;
        else if(constant.get_den()==1) out << QString::fromStdString(constant.get_str()) << key;
        else out << "⁜f⏴" << QString::fromStdString(constant.get_num().get_str()) << "⏵⏴"
                         << QString::fromStdString(constant.get_den().get_str()) << "⏵";
    }else{
        out << key;
    }
    if(prec > PREC_MULTIPLICATION) out << ')';
}

void ScalarMultiplication::foldConstants(){
    for(std::vector<Expr*>::size_type i = args.size()-1; i < args.size(); i--){
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
    for(std::vector<Expr*>::size_type i = args.size()-1; i < args.size(); i--){
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

    std::vector<Expr*>::size_type pattern_end = args.size() - 1;
    QString search_key = args.back()->getKey(PREC_MULTIPLICATION);
    std::vector<Expr*>::size_type i;
    for(i = pattern_end; i < args.size(); i--){
        QString target_key = args[i]->getKey(PREC_MULTIPLICATION);

        if(target_key != search_key){
            if(pattern_end - i > 1) collect(i+1, pattern_end);
            search_key = target_key;
            pattern_end = i;
        }
    }

    if(pattern_end - i > 1) collect(0, pattern_end);
}

void ScalarMultiplication::collect(vInt start, vInt end){
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

    vInt i = end+1;
    while(i --> start){
        if(args[i]->type == SCALAR_POWER){
            ScalarPower* p = static_cast<ScalarPower*>(args[i]);
            factors.push_back(p->rhs);
            if(p->lhs->type == SCALAR_MULTIPLICATION){
                n = new ScalarMultiplication(static_cast<ScalarMultiplication*>(p->lhs)->constant, n);
            }
            deleteRecursive(p->lhs);
            delete p;
        }else{
            factors.push_back(new Rational(1));
            if(args[i]->type == SCALAR_MULTIPLICATION){
                n = new ScalarMultiplication(static_cast<ScalarMultiplication*>(args[i])->constant, n);
            }
            deleteRecursive(args[i]);
        }
    }
    args.erase(args.begin()+start+1, args.begin()+end+1);

    Expr* zero_base = new Equality(n->clone());

    for(Expr* n : factors){
        Expr* exponent_is_positive =
            new Negation(
                new Disjunction(
                    {new Less(n->clone()),
                    new Equality(n->clone())}
                )
            );
        factors_positive.push_back( exponent_is_positive );
    }

    Expr* factored_exponent = new ScalarPower(n, new ScalarAddition(factors));
    Expr* positive_exponents = new Conjunction(factors_positive);
    Expr* is_defined = new Disjunction({new Negation(zero_base), positive_exponents});

    Expr* cv = new ConditionalValue(
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

QString ScalarMultiplication::getKey(Precedence prec) const{
    return (prec == PREC_ADDITION || prec == PREC_MULTIPLICATION) ? key : toMathBran();
}

}
