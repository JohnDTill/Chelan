#ifndef DISJUNCTION_H
#define DISJUNCTION_H

#include "expr.h"

namespace Chelan{

class Disjunction : public Expr{
public:
    std::vector<Expr*> args;
    QString key;

public:
    Disjunction(const std::vector<Expr*>& args);
    void processNewArg(Expr* n);
    virtual Expr* clone() const override;
    virtual void deleteChildren() override;
    virtual Expr* evaluate() override;
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const override;

private:
    void flatten(Disjunction* d);
    void insertOrDiscard(Expr* n);
    void setKey();
    static bool compare(const Expr* a, const Expr* b);
};

}

#endif // DISJUNCTION_H
