#include "pi.h"

namespace AST{

Pi::Pi()
    : Node(PI) {}

Node* Pi::clone() const{
    return new Pi();
}

Node* Pi::evaluate(){
    return nullptr;
}

QString Pi::toString(Precedence) const{
    return "π";
}

}
