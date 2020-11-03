#ifndef READVARIABLE_H
#define READVARIABLE_H

#include "expr.h"

namespace Chelan {

class Read : public Expr{
public:
    std::vector<Expr*>::size_type offset;

public:
    Read(std::vector<Expr*>::size_type offset);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // READVARIABLE_H
