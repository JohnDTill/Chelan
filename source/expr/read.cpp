#include "read.h"

#include "runtime.h"

namespace Chelan {

Read::Read(std::vector<Expr*>::size_type offset)
    : Expr(READ), offset(offset) {}

Expr* Read::clone() const{
    return new Read(offset);
}

Expr* Read::evaluate(Runtime& runtime){
    return Expr::evaluateAndFree(runtime.stack[runtime.stack.size()-offset]->clone(), runtime);
}

void Read::writeMathBran(QTextStream& out, Precedence) const{
    out << QString("⚠r(");
    out << offset;
    out << ')';
}

}
