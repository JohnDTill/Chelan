#ifndef UNTYPEDADDITION_H
#define UNTYPEDADDITION_H

#include "expr.h"

namespace Chelan{

class UntypedAddition : public Expr{
public:
    std::vector<Expr*> args;

public:
    UntypedAddition(const std::vector<Expr*>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;
};

}

#endif // UNTYPEDADDITION_H
