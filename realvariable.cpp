#include "realvariable.h"

namespace AST{

RealVariable::RealVariable(const ID& name)
    : Node(REALVARIABLE),
      name(name) {

}

Node* RealVariable::clone() const{
    return new RealVariable(name);
}

Node* RealVariable::evaluate(){
    return nullptr;
}

QString RealVariable::toMathBran(Precedence) const{
    return name;
}

}
