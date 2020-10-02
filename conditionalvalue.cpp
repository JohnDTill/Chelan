#include "conditionalvalue.h"

#include "chelan.h"

namespace Chelan{

ConditionalValue::ConditionalValue()
    : Expr(CONDITIONALVALUE) {}

ConditionalValue::ConditionalValue(Expr* condition, Expr* value_true, Expr* value_false)
    : Expr(CONDITIONALVALUE), values({value_true, value_false}), conditions({condition}) {}

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

void ConditionalValue::writeMathBran(QTextStream& out, Precedence) const{
    out << "⁜c⏴";
    values.front()->writeMathBran(out);
    for(std::vector<Expr*>::size_type i = 0; i < conditions.size(); i++){
        out << "⏵⏴";
        conditions[i]->writeMathBran(out);
        out << "⏵⏴";
        values[i+1]->writeMathBran(out);
    }
    out << "⏵⏴else⏵";
}

}
