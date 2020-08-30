#ifndef CONJUNCTION_H
#define CONJUNCTION_H

#include "expr.h"

namespace Chelan{

class Conjunction : public Expr{
public:
    std::vector<Expr*> args;
    QString key;

public:
    Conjunction();
    static Expr* And(Expr* lhs, Expr* rhs);
    static Expr* And(const std::vector<Expr*>& args);
    void processNewArg(Expr* n);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence prec = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;

private:
    void flatten(Conjunction* c);
    void insertOrDiscard(Expr* n);
    void setKey();
    static bool compare(const Expr* a, const Expr* b);
};

}

#endif // CONJUNCTION_H
