#include "realvariable.h"

namespace Chelan{

RealVariable::RealVariable(const ID& name)
    : Expr(REALVARIABLE), name(name) {}

Expr* RealVariable::clone() const{
    return new RealVariable(name);
}

Expr* RealVariable::evaluate(){
    return nullptr;
}

void RealVariable::writeMathBran(QTextStream& out, Precedence) const{
    out << name;
}

}
