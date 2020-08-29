#include "rational.h"

namespace AST{

Rational::Rational(const mpq_class& value)
    : Node(RATIONAL),
      value(value) {

}

Rational::Rational(const QString& value)
    : Node(RATIONAL),
      value(value.toStdString()) {

}

Node* Rational::clone() const{
    return new Rational(value);
}

Node* Rational::evaluate(){
    return nullptr;
}

QString Rational::toMathBran(Precedence prec) const{
    QString str = QString::fromStdString(value.get_str());
    if(prec >= PREC_MULTIPLICATION && value.get_den() != 1) str.prepend('(').append(')');
    return str;
}

}
