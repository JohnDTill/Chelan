#include "readlocal.h"

#include "runtime.h"

#include <QDebug>

namespace Chelan {

ReadLocal::ReadLocal(std::vector<Expr*>::size_type offset, const QString& id)
    : Expr(READ), offset(offset), id(id) {}

Expr* ReadLocal::clone() const{
    return new ReadLocal(offset, id);
}

Expr* ReadLocal::evaluate(Runtime& runtime){
    return Expr::evaluateAndFree(runtime.stack[runtime.stack.size()-offset]->clone(), runtime);
}

void ReadLocal::writeMathBran(QTextStream& out, Precedence) const{
    out << id;
}

}
