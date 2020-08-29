#include "undefined.h"

namespace Chelan{

Undefined::Undefined(const QString& msg)
    : Expr(UNDEFINED),
      msg(msg) {}

Expr* Undefined::clone() const{
    return new Undefined(msg);
}

Expr* Undefined::evaluate(){
    return nullptr;
}

QString Undefined::toMathBran(Expr::Precedence) const{
    return "undefined";
}

}
