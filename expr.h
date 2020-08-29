#ifndef NODE_H
#define NODE_H

#include "nodetype.h"
#include <QString>
#include <vector>

namespace Chelan{

class Expr{
public:
    const NodeType type;

protected:
    enum Precedence{
        PREC_NONE,
        PREC_DISJUNCTION, //DO THIS: logic nodes don't actually need precedence if
        PREC_CONJUNCTION, //         they are restricted to disjunctive normal form
        PREC_EQUALITY,
        PREC_LESS,
        PREC_NEGATION,
        PREC_ADDITION,
        PREC_MULTIPLICATION,
        PREC_POWER,
    };

public:
    Expr(const NodeType& type);
    virtual ~Expr();
    virtual Expr* clone() const = 0;
    virtual void deleteChildren(){}
    virtual Expr* evaluate() = 0;
    static Expr* evaluateAndFree(Expr* n);
    static void deleteRecursive(Expr* n);
    static Expr* remove(std::vector<Expr*>& search, const Expr* pattern, Precedence prec = PREC_NONE);
    static Expr* remove(std::vector<Expr*>& search, const Expr* pattern, const std::vector<Expr*>::iterator& end, Precedence prec = PREC_NONE);
    virtual QString toMathBran(Precedence prec = PREC_NONE) const = 0;
    virtual QString getKey(Precedence = PREC_NONE) const;
    bool isScalar() const;

protected:
    static Expr* searchForUndefined(const std::vector<Expr*>& args);
    template <Precedence prec = PREC_NONE> static bool compare(const Expr* a, const Expr* b){
        return a->getKey(prec) < b->getKey(prec);
    }
    static std::vector<Expr*> cloneArgs(const std::vector<Expr*> args);
    static bool isFalse(Expr* n);
    static bool isTrue(Expr* n);
};

}

#endif // NODE_H