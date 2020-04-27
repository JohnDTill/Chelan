#include "addition.h"

#include "chelan.h"

namespace AST{

Addition::Addition(const std::vector<Node*>& args)
    : Node(ADDITION),
      args(args) {}

Node* Addition::Add(Node* lhs, Node* rhs){
    return Node::evaluateAndFree(new Addition({lhs, rhs}));
}

Node* Addition::Add(Node* lhs, mpq_class rhs){
    Addition* a = new Addition({lhs});
    a->constant = rhs;

    return Node::evaluateAndFree(a);
}

Node*Addition::Add(mpq_class lhs, Node* rhs){
    Addition* a = new Addition({rhs});
    a->constant = lhs;

    return Node::evaluateAndFree(a);
}

Node* Addition::Add(const std::vector<Node*>& args){
    return Node::evaluateAndFree(new Addition(args));
}

Node* Addition::Subtract(Node* lhs, Node* rhs){
    return Add(lhs, Multiply(-1, rhs));
}

Node* Addition::clone() const{
    return new Addition(cloneArgs(args));
}

void Addition::deleteChildren(){
    for(Node* n : args){
        n->deleteChildren();
        delete n;
    }
}

Node* Addition::evaluate(){
    if(Node* n = searchForUndefined(args)) return n;
    foldConstants();
    flatten();
    collect();

    constant.canonicalize();
    if(args.size()==0) return Rational(constant);
    else if(args.size()==1 && constant==0) return *args.begin();

    setKey();
    return nullptr;
}

QString Addition::toString(Precedence prec) const{
    QString str = key;
    if(prec > PREC_ADDITION) str.prepend('(').append(')');

    return str;
}

void Addition::foldConstants(){
    auto it = args.end();
    do{
        Node* n = *(--it);
        if(n->type == RATIONAL){
            constant += static_cast<class Rational*>(n)->value;
            delete n;
            args.erase(it);
        }
    } while(it != args.begin());
}

void Addition::flatten(){
    if(args.empty()) return;

    std::vector<Node*> new_args;
    auto it = args.end();
    do{
        Node* n = *(--it);
        if(n->type == ADDITION){
            flatten(static_cast<Addition*>(n), new_args);
            delete n;
            args.erase(it);
        }
    } while(it != args.begin());

    for(Node* n : new_args) args.push_back(n);
}

void Addition::flatten(Addition* a, std::vector<Node*>& new_args){
    constant += a->constant;
    for(Node* n : a->args) new_args.push_back(n);
}

void Addition::collect(){
    if(args.size() < 2) return;

    std::sort(args.begin(), args.end(), compare<PREC_ADDITION>);

    auto pattern_end = args.end() - 1;
    QString search_key = args.back()->getKey(PREC_ADDITION);
    auto it = pattern_end;
    do{
        Node* n = *(--it);
        QString target_key = n->getKey(PREC_ADDITION);

        if(target_key != search_key){
            if(pattern_end - it > 1) collect(it+1, pattern_end);
            search_key = target_key;
            pattern_end = it;
        }
    } while(it != args.begin());

    if(pattern_end - it > 0) collect(it, pattern_end);
}

void Addition::collect(std::vector<Node*>::iterator start, std::vector<Node*>::iterator end){
    mpq_class factor = 0;
    Node* n = (*start)->clone();
    if(n->type == MULTIPLICATION)
        static_cast<Multiplication*>(n)->constant = 1;


    for(auto it = end; it >= start; it--){
        Node* n = *it;
        if(n->type == MULTIPLICATION){
            factor += static_cast<Multiplication*>(n)->constant;
        }else{
            factor++;
        }
        deleteRecursive(n);
    }

    args.erase(start, end+1);

    Node* factored = Multiply(factor, n);
    if(factored->type != RATIONAL) args.insert(start, Multiply(factor, n));
    else delete factored;
}

void Addition::setKey(){
    std::sort(args.begin(), args.end(), compare<PREC_ADDITION>);

    if(constant!=0) key = QString::fromStdString(constant.get_str()) + " + ";
    key += args[0]->toString(PREC_ADDITION);
    for(std::vector<Node*>::size_type i = 1; i < args.size(); i++)
        key += " + " + args[i]->toString(PREC_ADDITION);
}

}
