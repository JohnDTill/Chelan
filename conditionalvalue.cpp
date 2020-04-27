#include "conditionalvalue.h"

namespace AST{

ConditionalValue::ConditionalValue()
    : Node(CONDITIONALVALUE) {

}

ConditionalValue::ConditionalValue(Node* condition, Node* value_true, Node* value_false)
    : Node(CONDITIONALVALUE) {
    conditions.push_back(condition);
    values.push_back(value_true);
    values.push_back(value_false);
}

Node* ConditionalValue::Ternary(Node* condition, Node* value_true, Node* value_false){
    return Node::evaluateAndFree( new ConditionalValue(condition, value_true, value_false) );
}

Node* ConditionalValue::clone() const{
    ConditionalValue* c = new ConditionalValue();
    for(Node* n : values) c->values.push_back(n->clone());
    for(Node* n : conditions) c->conditions.push_back(n->clone());

    return c;
}

void ConditionalValue::deleteChildren(){
    for(Node* n : values){
        n->deleteChildren();
        delete n;
    }
    for(Node* n : conditions){
        n->deleteChildren();
        delete n;
    }
}

Node* ConditionalValue::evaluate(){
    for(std::vector<Node*>::size_type i = 0; i < conditions.size(); i++){
        if(isTrue(conditions[i])){
            Node* n = values[i]->clone();
            deleteChildren();

            return n;
        }
    }

    return nullptr;
}

QString ConditionalValue::toString(Node::Precedence) const{
    QString str = "{" + values.front()->toString();
    for(std::vector<Node*>::size_type i = 0; i < conditions.size(); i++){
        str += " if " + conditions[i]->toString() + ", " + values[i+1]->toString();
    }
    str += " else";

    return str;
}

}
