#ifndef UNTYPEDIMPLICITMULT_H
#define UNTYPEDIMPLICITMULT_H

#include "expr.h"

namespace Chelan{

class UntypedImplicitMult : public Expr{
public:
    std::vector<Expr*> args;

public:
    UntypedImplicitMult(const std::vector<Expr*>& args);
    virtual Expr* clone() const override;
    virtual Expr* evaluate() override;
    virtual QString toMathBran(Precedence = PREC_NONE) const override;
    virtual void visitChildren(Interpreter* interpreter) override;
    Expr* evaluate(QString& err_msg);
};

}

#endif // UNTYPEDIMPLICITMULT_H
