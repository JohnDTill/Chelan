#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "expr.h"
#include "undefined.h"
#include <gmpxx.h>

namespace Chelan{

class ScalarMultiplication : public Expr{
public:
    std::vector<Expr*> args;
    QString key;
    mpq_class constant = 1;

public:
    ScalarMultiplication(const std::vector<Expr*>& args);
    static Expr* Multiply(Expr* lhs, Expr* rhs);
    static Expr* Multiply(mpq_class lhs, Expr* rhs);
    static Expr* Multiply(const std::vector<Expr*>& args);
    static Expr* Divide(Expr* lhs, Expr* rhs);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;

private:
    void foldConstants();
    void flatten();
    void flatten(ScalarMultiplication* a, std::vector<Expr*>& new_args);
    void collect();
    void collect(int start, int end);
    void setKey();
    virtual QString getKey(Precedence prec = PREC_NONE) const override;
};

}

#endif // MULTIPLICATION_H
