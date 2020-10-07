#include "rational.h"

namespace Chelan{

Rational::Rational(const mpq_class& value)
    : Expr(RATIONAL), value(value) {}

Rational::Rational(int value)
    : Expr(RATIONAL), value(value) {}

Rational::Rational(const QString& value)
    : Expr(RATIONAL), value(value.toStdString()) {}

Expr* Rational::clone() const{
    return new Rational(value);
}

Expr* Rational::evaluate(){
    return nullptr;
}

void Rational::writeMathBran(QTextStream& out, Precedence prec) const{
    if(prec >= PREC_MULTIPLICATION && value.get_den() != 1)
        out << '(' << QString::fromStdString(value.get_str()) << ')';
    else
        out << QString::fromStdString(value.get_str());
}

}
