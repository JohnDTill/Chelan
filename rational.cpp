#include "rational.h"

namespace Chelan{

Rational::Rational(const mpq_class& value)
    : Expr(RATIONAL),
      value(value) {

}

Rational::Rational(const QString& value)
    : Expr(RATIONAL),
      value(value.toStdString()) {

}

Expr* Rational::clone() const{
    return new Rational(value);
}

Expr* Rational::evaluate(){
    return nullptr;
}

QString Rational::toMathBran(Precedence prec) const{
    QString str = QString::fromStdString(value.get_str());
    if(prec >= PREC_MULTIPLICATION && value.get_den() != 1) str.prepend('(').append(')');
    return str;
}

void Rational::visitChildren(Interpreter* interpreter){
    //DO NOTHING
}

}
