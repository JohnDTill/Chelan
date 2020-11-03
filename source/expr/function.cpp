#include "function.h"

#include "stmt.h"

namespace Chelan {

Function::Function(Stmt* body)
    : Expr(FUNCTION), body(body) {}

Expr* Function::clone() const{
    return new Function(body);
}

Expr* Function::evaluate(Runtime&){
    return this;
}

void Function::writeMathBran(QTextStream& out, Precedence) const{
    out << "FUNCTION";
}

}
