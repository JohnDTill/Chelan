#include "realvariable.h"

namespace Chelan{

RealVariable::RealVariable(const ID& name)
    : Expr(REALVARIABLE),
      name(name) {

}

Expr* RealVariable::clone() const{
    return new RealVariable(name);
}

Expr* RealVariable::evaluate(){
    return nullptr;
}

QString RealVariable::toMathBran(Precedence) const{
    return name;
}

void RealVariable::visitChildren(Interpreter*){
    //DO NOTHING
}

}
