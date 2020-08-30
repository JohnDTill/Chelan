#include "read.h"

namespace Chelan {

Read::Read(std::vector<Expr*>::size_type slot)
    : Expr(READ), slot(slot) {

}

Expr* Read::clone() const{
    return new Read(slot);
}

Expr* Read::evaluate(){
    //DO THIS
    return nullptr;
}

QString Read::toMathBran(Expr::Precedence) const{
    //This highlights a gap in my philosophy- calling a read an expression is a bit of an abuse
    return "⁜r" + QString::number(slot);
}

void Read::visitChildren(Interpreter* interpreter){
    //DO NOTHING
}

}
