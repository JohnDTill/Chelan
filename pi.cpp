#include "pi.h"

namespace Chelan{

Pi::Pi()
    : Expr(PI) {}

Expr* Pi::clone() const{
    return new Pi();
}

Expr* Pi::evaluate(){
    return nullptr;
}

QString Pi::toMathBran(Precedence) const{
    return "π";
}

void Pi::visitChildren(Interpreter*){
    //DO NOTHING
}

}
