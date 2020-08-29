#include "untypedaddition.h"

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

}
