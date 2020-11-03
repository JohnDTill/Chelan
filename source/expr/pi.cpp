#include "pi.h"

namespace Chelan{

Pi::Pi()
    : Expr(PI) {}

Expr* Pi::clone() const{
    return new Pi();
}

Expr* Pi::evaluate(Runtime&){
    return nullptr;
}

void Pi::writeMathBran(QTextStream& out, Precedence) const{
    out << QString("π");
}

}
