#ifndef CALL_H
#define CALL_H

#include "expr.h"

namespace Chelan{

class Function;

class Call : public Expr{
private:
    Expr* f;
    std::vector<Expr*> args;
    bool has_return_value;

public:
    Call(Expr* f, std::vector<Expr*> args, bool has_return_value);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime& runtime) override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;
};

}

#endif // CALL_H
