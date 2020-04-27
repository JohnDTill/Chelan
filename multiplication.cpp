#include "multiplication.h"

#include "chelan.h"

namespace AST{

Multiplication::Multiplication(const std::vector<Node*>& args)
    : Node(MULTIPLICATION),
      args(args) {}

Node* Multiplication::Multiply(Node* lhs, Node* rhs){
    return Node::evaluateAndFree(new Multiplication({lhs, rhs}));
}

Node* Multiplication::Multiply(mpq_class lhs, Node* rhs){
    Multiplication* m = new Multiplication({rhs});
    m->constant = lhs;

    return Node::evaluateAndFree(m);
}

Node* Multiplication::Multiply(const std::vector<Node*>& args){
    return Node::evaluateAndFree(new Multiplication(args));
}

Node* Multiplication::Divide(Node* lhs, Node* rhs){
    return Multiply(lhs, Raise(rhs, -1));
}

Node* Multiplication::clone() const{
    return new Multiplication(cloneArgs(args));
}

void Multiplication::deleteChildren(){
    for(Node* n : args){
        n->deleteChildren();
        delete n;
    }
}

Node* Multiplication::evaluate(){
    if(Node* n = searchForUndefined(args)) return n;
    foldConstants();
    flatten();
    collect();

    constant.canonicalize();

    if(args.size()==0){
        return Rational(constant);
    }else if(constant == 0){
        //DO THIS: 0*x => 0 only if x is defined
        //if(IsDefined(args))...
        deleteChildren();
        return Rational(constant);
    }else if(args.size()==1 && constant==1){
        return *args.begin();
    }

    setKey();

    return nullptr;
}

QString Multiplication::toString(Precedence prec) const{
    QString str = key;
    if(constant!=1) str.prepend(QString::fromStdString(constant.get_str()) + '*');
    if(prec > PREC_MULTIPLICATION) str.prepend('(').append(')');

    return str;
}

void Multiplication::foldConstants(){
    auto it = args.end();
    do{
        Node* n = *(--it);
        if(n->type == RATIONAL){
            constant *= static_cast<class Rational*>(n)->value;
            delete n;
            args.erase(it);
        }
    } while(it != args.begin());
}

void Multiplication::flatten(){
    if(args.empty()) return;

    std::vector<Node*> new_args;
    auto it = args.end();
    do{
        Node* n = *(--it);
        if(n->type == ADDITION){
            flatten(static_cast<Multiplication*>(n), new_args);
            delete n;
            args.erase(it);
        }
    } while(it != args.begin());

    for(Node* n : new_args) args.push_back(n);
}

void Multiplication::flatten(Multiplication* a, std::vector<Node*>& new_args){
    constant *= a->constant;
    for(Node* n : a->args) new_args.push_back(n);
}

void Multiplication::collect(){
    if(args.size() < 2) return;

    std::sort(args.begin(), args.end(), compare<PREC_MULTIPLICATION>);

    auto pattern_end = args.end() - 1;
    QString search_key = args.back()->getKey(PREC_MULTIPLICATION);
    auto it = pattern_end;
    do{
        Node* n = *(--it);
        QString target_key = n->getKey(PREC_MULTIPLICATION);

        if(target_key != search_key){
            if(pattern_end - it > 1) collect(it+1, pattern_end);
            search_key = target_key;
            pattern_end = it;
        }
    } while(it != args.begin());

    if(pattern_end - it > 0) collect(it, pattern_end);
}

void Multiplication::collect(std::vector<Node*>::iterator start, std::vector<Node*>::iterator end){
    std::vector<Node*> factors;
    std::vector<Node*> factors_positive;
    Node* n = (*start)->clone();
    if(n->type == POWER){
        Power* p = static_cast<Power*>(n);
        deleteRecursive(p->rhs);
        n = p->lhs;
        delete p;
    }

    for(auto it = end; it >= start; it--){
        Node* n = *it;
        if(n->type == POWER){
            factors.push_back(static_cast<Power*>(n)->rhs->clone());
        }else{
            factors.push_back(Rational(1));
        }
        deleteRecursive(n);
    }
    args.erase(start, end+1);

    Node* zero_base = EqualsZero(n->clone());

    for(Node* n : factors){
        Node* exponent_is_positive =
            Not(
                Or(
                    IsLessThanZero(n->clone()),
                    EqualsZero(n->clone())
                )
            );
        factors_positive.push_back( exponent_is_positive );
    }

    Node* factored_exponent = Raise(n, Add(factors));
    Node* positive_exponents = And(factors_positive);
    Node* is_defined = Or(Not(zero_base), positive_exponents);

    Node* cv = Ternary(
                   is_defined,
                   factored_exponent,
                   new Undefined("Divide by 0")
               );
    args.insert(start, cv);
}

void Multiplication::setKey(){
    std::sort(args.begin(), args.end(), compare<PREC_MULTIPLICATION>);
    key = args[0]->toString(PREC_ADDITION);
    for(std::vector<Node*>::size_type i = 1; i < args.size(); i++)
        key += "*" + args[i]->toString(PREC_ADDITION);
}

QString Multiplication::getKey(Node::Precedence prec) const{
    return (prec == PREC_ADDITION) ? key : toString();
}

}
