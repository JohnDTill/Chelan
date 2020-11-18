#ifndef READLOCALELEMENT_H
#define READLOCALELEMENT_H

#include "expr.h"

namespace Chelan {

class ReadLocalElement : public Expr{
public:
    std::vector<Expr*>::size_type offset;
    QString id;
    Expr* index;

public:
    ReadLocalElement(std::vector<Expr*>::size_type offset, const QString& id, Expr* index);
    virtual Expr* clone() const override;
    virtual Expr* evaluate(Runtime&) override;
    virtual void writeMathBran(QTextStream& out, Precedence = PREC_NONE) const override;
};

}

#endif // READLOCALELEMENT_H
