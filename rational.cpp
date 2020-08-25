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

QString Rational::toMathBran(Precedence) const{
    return QString::fromStdString(value.get_str());
}

}
