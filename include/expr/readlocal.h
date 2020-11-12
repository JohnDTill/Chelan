#ifndef READVARIABLE_H
#define READVARIABLE_H

#include "expr.h"

namespace Chelan {

class ReadLocal : public Expr{
public:
    std::vector<Expr*>::size_type offset;
    QString id;

public:
    ReadLocal(std::vector<Expr*>::size_type offset, const QString& id);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // READVARIABLE_H
