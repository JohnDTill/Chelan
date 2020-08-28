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

QString Addition::toMathBran(Precedence prec) const{
    QString str = key;
    if(prec > PREC_ADDITION) str.prepend('(').append(')');

    return str;
}

void Addition::foldConstants(){
    for(int i = args.size()-1; i >= 0; i--){
        if(args[i]->type == RATIONAL){
            constant += static_cast<class Rational*>(args[i])->value;
            delete args[i];
            args.erase(args.begin()+i);
        }
    }
}

void Addition::flatten(){
    if(args.empty()) return;

    std::vector<Node*> new_args;
    for(int i = args.size()-1; i >= 0; i--){
        if(args[i]->type == ADDITION){
            flatten(static_cast<Addition*>(args[i]), new_args);
            delete args[i];
            args.erase(args.begin()+i);
        }
    }

    for(Node* n : new_args) args.push_back(n);
}

void Addition::flatten(Addition* a, std::vector<Node*>& new_args){
    constant += a->constant;
    for(Node* n : a->args) new_args.push_back(n);
}

void Addition::collect(){
    if(args.size() < 2) return;

    std::sort(args.begin(), args.end(), compare<PREC_ADDITION>);

    int pattern_end = args.size() - 1;
    QString search_key = args.back()->getKey(PREC_ADDITION);
    int i;
    for(i = pattern_end; i >= 0; i--){
        QString target_key = args[i]->getKey(PREC_ADDITION);

        if(target_key != search_key){
            if(pattern_end - i > 1) collect(i+1, pattern_end);
            search_key = target_key;
            pattern_end = i;
        }
    }

    if(pattern_end - i > 1) collect(0, pattern_end);
}

void Addition::collect(int start, int end){
    mpq_class factor = 0;
    Node* n = args[start]->clone();
    if(n->type == MULTIPLICATION)
        static_cast<Multiplication*>(n)->constant = 1;


    for(int i = end; i >= start; i--){
        if(args[i]->type == MULTIPLICATION){
            factor += static_cast<Multiplication*>(args[i])->constant;
        }else{
            factor++;
        }
        deleteRecursive(args[i]);
    }

    Node* factored = Multiply(factor, n);
    if(factored->type != RATIONAL){
        args[start] = factored;
        args.erase(args.begin()+start+1, args.begin()+end+1);
    }else{
        deleteRecursive(factored);
        args.erase(args.begin()+start, args.begin()+end+1);
    }
}

void Addition::setKey(){
    std::sort(args.begin(), args.end(), compare<PREC_ADDITION>);

    if(constant!=0) key = QString::fromStdString(constant.get_str()) + " + ";
    key += args[0]->toMathBran(PREC_ADDITION);
    for(std::vector<Node*>::size_type i = 1; i < args.size(); i++)
        key += " + " + args[i]->toMathBran(PREC_ADDITION);
}

}
