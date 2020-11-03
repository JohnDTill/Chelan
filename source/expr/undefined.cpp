#include "undefined.h"

namespace Chelan{

Undefined::Undefined(const QString& msg, bool type_error)
    : Expr(UNDEFINED),
      msg(msg),
      type_error(type_error) {}

Expr* Undefined::clone() const{
    return new Undefined(msg);
}

Expr* Undefined::evaluate(Runtime&){
    return nullptr;
}

void Undefined::writeMathBran(QTextStream& out, Precedence) const{
    out << "undefined";
}

}
