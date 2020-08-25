#include "node.h"

#include "chelan.h"

namespace AST{

Node::Node(const NodeType& type)
    : type(type) {

}

Node::~Node(){
    //DO NOTHING
}

Node* Node::evaluateAndFree(Node* n){
    if(Node* m = n->evaluate()){
        delete n; //The evaluate call should delete n's children as necessary to prevent leaks
        return m;
    }else{
        return n;
    }
}

void Node::deleteRecursive(Node* n){
    n->deleteChildren();
    delete n;
}

Node* Node::remove(std::vector<Node*>& search, const Node* pattern, Precedence prec){
    QString p_str = pattern->getKey(prec);

    for(std::vector<Node*>::iterator it = search.begin(); it != search.end(); it++){
        Node* n = *it;
        if(n->getKey(prec) == p_str){
            search.erase(it);
            return n;
        }
    }

    return nullptr;
}

Node* Node::remove(std::vector<Node*>& search, const Node* pattern, const std::vector<Node*>::iterator& end, Precedence prec){
    QString p_str = pattern->getKey(prec);
    for(auto it = search.begin(); it != end; it++){
        Node* n = *it;
        if(n->getKey(prec) == p_str){
            search.erase(it);
            return n;
        }
    }

    return nullptr;
}

QString Node::getKey(Precedence) const{
    return toMathBran();
}

Node* Node::searchForUndefined(const std::vector<Node*>& args){
    for(std::vector<Node*>::size_type i = 0; i < args.size(); i++){
        if(args[i]->type == UNDEFINED){
            for(std::vector<Node*>::size_type j = 0; j < i; j++) deleteRecursive(args[j]);
            for(std::vector<Node*>::size_type j = i+1; j < args.size(); j++) deleteRecursive(args[j]);

            return args[i];
        }
    }

    return nullptr;
}

std::vector<Node*> Node::cloneArgs(const std::vector<Node*> args){
    std::vector<Node*> args_clone;
    args_clone.resize(args.size());
    for(std::vector<Node*>::size_type i = 0; i < args.size(); i++)
        args_clone[i] = args[i]->clone();

    return args_clone;
}

bool Node::isFalse(Node* n){
    return n->type == BOOLEAN && static_cast<Boolean*>(n)->value == false;
}

bool Node::isTrue(Node* n){
    return n->type == BOOLEAN && static_cast<Boolean*>(n)->value == true;
}

}
