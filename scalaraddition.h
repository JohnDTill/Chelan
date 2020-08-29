#ifndef ADDITION_H
#define ADDITION_H

#include "expr.h"
#include <gmpxx.h>

namespace Chelan{

class ScalarAddition : public Expr{
public:
    std::vector<Expr*> args;
    mpq_class constant = 0;
    QString key;

public:
    ScalarAddition(const std::vector<Expr*>& args);
    static Expr* Add(Expr* lhs, Expr* rhs);
    static Expr* Add(Expr* lhs, mpq_class rhs);
    static Expr* Add(mpq_class lhs, Expr* rhs);
    static Expr* Add(const std::vector<Expr*>& args);
    static Expr* Subtract(Expr* lhs, Expr* rhs);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;

private:
    void foldConstants();
    void flatten();
    void flatten(ScalarAddition* a, std::vector<Expr*>& new_args);
    void collect();
    void collect(int start, int end);
    void setKey();
};

}

#endif // ADDITION_H
