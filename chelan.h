#ifndef CHELAN_H
#define CHELAN_H

#include <QDebug>

#include "scalaraddition.h"
#include "boolean.h"
#include "conditionalvalue.h"
#include "conjunction.h"
#include "disjunction.h"
#include "equality.h"
#include "less.h"
#include "matrix.h"
#include "scalarmultiplication.h"
#include "negation.h"
#include "pi.h"
#include "scalarpower.h"
#include "rational.h"
#include "realvariable.h"
#include "undefined.h"

namespace Chelan{

inline Expr* Add(Expr* lhs, Expr* rhs){ return ScalarAddition::Add(lhs, rhs); }
inline Expr* Add(Expr* lhs, mpq_class rhs){ return ScalarAddition::Add(lhs, rhs); }
inline Expr* Add(mpq_class lhs, Expr* rhs){ return ScalarAddition::Add(lhs, rhs); }
inline Expr* Add(const std::vector<Expr*>& args){ return ScalarAddition::Add(args); }
inline Expr* And(Expr* lhs, Expr* rhs){ return Conjunction::And(lhs, rhs); }
inline Expr* And(const std::vector<Expr*>& args){ return Conjunction::And(args); }
inline Expr* Divide(Expr* lhs, Expr* rhs){ return ScalarMultiplication::Divide(lhs, rhs); }
inline Expr* Equals(Expr* lhs, Expr* rhs){ return Equality::Equals(lhs, rhs); }
inline Expr* EqualsZero(Expr* n){ return Equality::EqualsZero(n); }
inline Expr* False(){ return new Boolean(false); }
inline Expr* IsLess(Expr* lhs, Expr* rhs){ return Less::IsLess(lhs, rhs); }
inline Expr* IsLessThanZero(Expr* n){ return Less::IsLessThanZero(n); }
inline Expr* Multiply(Expr* lhs, Expr* rhs){ return ScalarMultiplication::Multiply(lhs, rhs); }
inline Expr* Multiply(mpq_class lhs, Expr* rhs){ return ScalarMultiplication::Multiply(lhs, rhs); }
inline Expr* Multiply(const std::vector<Expr*>& args){ return ScalarMultiplication::Multiply(args); }
inline Expr* Not(Expr* n){ return Negation::Not(n); }
inline Expr* Or(Expr* lhs, Expr* rhs){ return Disjunction::Or(lhs, rhs); }
inline Expr* Or(const std::vector<Expr*>& args){ return Disjunction::Or(args); }
inline Expr* Pi(){ return new class Pi(); }
inline Expr* Raise(Expr* lhs, Expr* rhs){ return ScalarPower::Raise(lhs, rhs); }
inline Expr* Raise(Expr* lhs, mpq_class rhs){ return ScalarPower::Raise(lhs, rhs); }
inline Expr* Rational(const mpq_class& value){ return new class Rational(value); }
inline Expr* Rational(const QString& value){ return new class Rational(value); }
inline Expr* RealVariable(const ID& name){ return new class RealVariable(name); }
inline Expr* Subtract(Expr* lhs, Expr* rhs){ return ScalarAddition::Subtract(lhs, rhs); }
inline Expr* Ternary(Expr* condition, Expr* value_true, Expr* value_false){ return ConditionalValue::Ternary(condition, value_true, value_false); }
inline Expr* True(){ return new Boolean(true); }

}

#endif // CHELAN_H
