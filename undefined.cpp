#include "undefined.h"

namespace Chelan{

Undefined::Undefined(const QString& msg, bool type_error)
    : Expr(UNDEFINED),
      msg(msg),
      type_error(type_error) {}

Expr* Undefined::clone() const{
    return new Undefined(msg);
}

Expr* Undefined::evaluate(){
    return nullptr;
}

QString Undefined::toMathBran(Expr::Precedence) const{
    return "undefined";
}

void Undefined::visitChildren(Interpreter*){
    //DO NOTHING
}

}
