#include "boolean.h"

namespace AST{

Boolean::Boolean(const bool& value)
    : Node(BOOLEAN),
      value(value) {}

Node* Boolean::clone() const{
    return new Boolean(value);
}

Node* Boolean::evaluate(){
    return nullptr;
}

QString Boolean::toMathBran(Node::Precedence) const{
    return value ? "1" : "0";
}

}
