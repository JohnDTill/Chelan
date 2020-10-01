#include "boolean.h"

namespace Chelan{

Boolean::Boolean(const bool& value)
    : Expr(BOOLEAN_VALUE), value(value) {}

Expr* Boolean::clone() const{
    return new Boolean(value);
}

Expr* Boolean::evaluate(){
    return nullptr;
}

QString Boolean::toMathBran(Precedence) const{
    return value ? "true" : "false";
}

}
