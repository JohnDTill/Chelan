#ifndef CHELAN_H
#define CHELAN_H

#include <QDebug>

#include "addition.h"
#include "boolean.h"
#include "conditionalvalue.h"
#include "conjunction.h"
#include "disjunction.h"
#include "equality.h"
#include "less.h"
#include "multiplication.h"
#include "negation.h"
#include "pi.h"
#include "power.h"
#include "rational.h"
#include "realvariable.h"
#include "undefined.h"

namespace AST{

inline Node* Add(Node* lhs, Node* rhs){ return Addition::Add(lhs, rhs); }
inline Node* Add(Node* lhs, mpq_class rhs){ return Addition::Add(lhs, rhs); }
inline Node* Add(mpq_class lhs, Node* rhs){ return Addition::Add(lhs, rhs); }
inline Node* Add(const std::vector<Node*>& args){ return Addition::Add(args); }
inline Node* And(Node* lhs, Node* rhs){ return Conjunction::And(lhs, rhs); }
inline Node* And(const std::vector<Node*>& args){ return Conjunction::And(args); }
inline Node* Divide(Node* lhs, Node* rhs){ return Multiplication::Divide(lhs, rhs); }
inline Node* Equals(Node* lhs, Node* rhs){ return Equality::Equals(lhs, rhs); }
inline Node* EqualsZero(Node* n){ return Equality::EqualsZero(n); }
inline Node* False(){ return new Boolean(false); }
inline Node* IsLess(Node* lhs, Node* rhs){ return Less::IsLess(lhs, rhs); }
inline Node* IsLessThanZero(Node* n){ return Less::IsLessThanZero(n); }
inline Node* Multiply(Node* lhs, Node* rhs){ return Multiplication::Multiply(lhs, rhs); }
inline Node* Multiply(mpq_class lhs, Node* rhs){ return Multiplication::Multiply(lhs, rhs); }
inline Node* Multiply(const std::vector<Node*>& args){ return Multiplication::Multiply(args); }
inline Node* Not(Node* n){ return Negation::Not(n); }
inline Node* Or(Node* lhs, Node* rhs){ return Disjunction::Or(lhs, rhs); }
inline Node* Or(const std::vector<Node*>& args){ return Disjunction::Or(args); }
inline Node* Pi(){ return new class Pi(); }
inline Node* Raise(Node* lhs, Node* rhs){ return Power::Raise(lhs, rhs); }
inline Node* Raise(Node* lhs, mpq_class rhs){ return Power::Raise(lhs, rhs); }
inline Node* Rational(const mpq_class& value){ return new class Rational(value); }
inline Node* Rational(const QString& value){ return new class Rational(value); }
inline Node* RealVariable(const ID& name){ return new class RealVariable(name); }
inline Node* Subtract(Node* lhs, Node* rhs){ return Addition::Subtract(lhs, rhs); }
inline Node* Ternary(Node* condition, Node* value_true, Node* value_false){ return ConditionalValue::Ternary(condition, value_true, value_false); }
inline Node* True(){ return new Boolean(true); }

}

#endif // CHELAN_H
