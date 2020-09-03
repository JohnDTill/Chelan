#include "conditionalvalue.h"

#include "chelan.h"

namespace Chelan{

ConditionalValue::ConditionalValue()
    : Expr(CONDITIONALVALUE) {

}

ConditionalValue::ConditionalValue(Expr* condition, Expr* value_true, Expr* value_false)
    : Expr(CONDITIONALVALUE) {
    conditions.push_back(condition);
    values.push_back(value_true);
    values.push_back(value_false);
}

Expr* ConditionalValue::clone() const{
    ConditionalValue* c = new ConditionalValue();
    for(Expr* n : values) c->values.push_back(n->clone());
    for(Expr* n : conditions) c->conditions.push_back(n->clone());

    return c;
}

void ConditionalValue::deleteChildren(){
    for(Expr* n : values){
        n->deleteChildren();
        delete n;
    }
    for(Expr* n : conditions){
        n->deleteChildren();
        delete n;
    }
}

Expr* ConditionalValue::evaluate(){
    for(std::vector<Expr*>::size_type i = 0; i < conditions.size(); i++){
        if(isTrue(conditions[i])){
            Expr* n = values[i]->clone();
            deleteChildren();

            return n;
        }
    }

    return nullptr;
}

QString ConditionalValue::toMathBran(Expr::Precedence) const{
    QString str = "⁜c⏴" + values.front()->toMathBran();
    for(std::vector<Expr*>::size_type i = 0; i < conditions.size(); i++){
        str += "⏵⏴" + conditions[i]->toMathBran() + "⏵⏴" + values[i+1]->toMathBran();
    }
    str += "⏵⏴else⏵";

    return str;
}

void ConditionalValue::visitChildren(Interpreter* interpreter){
    for(Expr* expr : values) expr = interpreter->evaluate(expr);
    for(Expr* expr : conditions) expr = interpreter->evaluate(expr);
}

}
