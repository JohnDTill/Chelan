#ifndef CONDITIONALVALUE_H
#define CONDITIONALVALUE_H

#include "expr.h"

namespace Chelan{

class ConditionalValue : public Expr{
private:
    std::vector<Expr*> values;
    std::vector<Expr*> conditions;

public:
    ConditionalValue();
    ConditionalValue(Expr* condition, Expr* value_true, Expr* value_false);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // CONDITIONALVALUE_H
