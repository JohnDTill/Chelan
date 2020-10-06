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

static QString labels[2] = {"false", "true"};
void Boolean::writeMathBran(QTextStream& out, Precedence) const{
    out << labels[value];
}

}
