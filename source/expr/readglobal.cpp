#include "readglobal.h"

#include "runtime.h"

namespace Chelan {

ReadGlobal::ReadGlobal(std::vector<Expr*>::size_type offset, const QString& id)
    : Expr(READ), offset(offset), id(id) {}

Expr* ReadGlobal::clone() const{
    return new ReadGlobal(offset, id);
}

Expr* ReadGlobal::evaluate(Runtime& runtime){
    return Expr::evaluateAndFree(runtime.stack[offset]->clone(), runtime);
}

void ReadGlobal::writeMathBran(QTextStream& out, Precedence) const{
    out << id;
}

}
