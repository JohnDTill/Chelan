#ifndef NODE_H
#define NODE_H

#include "exprtype.h"
#include <QString>
#include <QTextStream>
#include <vector>
class QTextStream;

namespace Chelan{

class Runtime;

enum Precedence{
    PREC_NONE,
    PREC_DISJUNCTION,
    PREC_CONJUNCTION,
    PREC_EQUALITY,
    PREC_LESS,
    PREC_NEGATION,
    PREC_ADDITION,
    PREC_MULTIPLICATION,
    PREC_POWER,
};

class Expr{
public:
    const ExprType type;

public:
    Expr(const ExprType& type);
    virtual ~Expr();
    virtual Expr* clone() const = 0;
    virtual void deleteChildren(){}
    virtual Expr* evaluate(Runtime& runtime) = 0;
    static Expr* evaluateAndFree(Expr* n, Runtime& runtime);
    static void deleteRecursive(Expr* n);
    static Expr* remove(std::vector<Expr*>& search, const Expr* pattern, Precedence prec = PREC_NONE);
    static Expr* remove(std::vector<Expr*>& search, const Expr* pattern, const std::vector<Expr*>::iterator& end, Precedence prec = PREC_NONE);
    virtual void writeMathBran(QTextStream& out, Precedence prec = PREC_NONE) const = 0;
    QString toMathBran(Precedence prec = PREC_NONE) const;
    virtual QString getKey(Precedence = PREC_NONE) const;
    virtual bool isDefinitivelyFalse() const {return false;}
    virtual bool isDefinitivelyTrue() const {return false;}

protected:
    static Expr* searchForUndefined(const std::vector<Expr*>& args);
    template <Precedence prec = PREC_NONE> static bool compare(const Expr* a, const Expr* b){
        return a->getKey(prec) < b->getKey(prec);
    }
    static std::vector<Expr*> cloneArgs(const std::vector<Expr*>& args);
    static void evaluateAndFreeArgs(std::vector<Expr*>& args, Runtime& runtime);
};

typedef std::vector<Expr*>::size_type vInt;

}

#endif // NODE_H
