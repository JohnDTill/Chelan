#ifndef READGLOBAL_H
#define READGLOBAL_H

#include "expr.h"

namespace Chelan {

class ReadGlobal : public Expr{
public:
    std::vector<Expr*>::size_type offset;
    QString id;

public:
    ReadGlobal(std::vector<Expr*>::size_type offset, const QString& id);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // READGLOBAL_H
