#include "untypedaddition.h"

#include "chelan.h"

namespace Chelan{

UntypedAddition::UntypedAddition(const std::vector<Expr*>& args)
    : Expr(UNTYPED_ADDITION) {
    //DO THIS
}

Expr* UntypedAddition::clone() const{
    //DO THIS
    return nullptr;
}

Expr* UntypedAddition::evaluate(){
    return nullptr;
}

QString UntypedAddition::toMathBran(Expr::Precedence) const{
    //DO THIS
    return QString();
}

void UntypedAddition::visitChildren(Interpreter* interpreter){
    for(Expr* expr : args) expr = interpreter->evaluate(expr);
}

}
