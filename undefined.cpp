#include "undefined.h"

namespace AST{

Undefined::Undefined(const QString& msg)
    : Node(UNDEFINED),
      msg(msg) {}

Node* Undefined::clone() const{
    return new Undefined(msg);
}

Node* Undefined::evaluate(){
    return nullptr;
}

QString Undefined::toString(Node::Precedence) const{
    return "undefined";
}

}
