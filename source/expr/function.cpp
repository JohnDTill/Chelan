#include "function.h"

#include "stmt.h"

namespace Chelan {

Function::Function(Stmt* body, QString id)
    : Expr(FUNCTION), body(body), id(id) {}

Expr* Function::clone() const{
    return new Function(body, id);
}

Expr* Function::evaluate(Runtime&){
    return nullptr;
}

void Function::writeMathBran(QTextStream& out, Precedence) const{
    out << id;
}

}
