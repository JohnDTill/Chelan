#ifndef NODE_H
#define NODE_H

#include "exprtype.h"
#include <QString>
#include <vector>
class QTextStream;

namespace Chelan{

class Interpreter;

class Expr{
public:
    const ExprType type;

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
    Expr(const ExprType& type);
    virtual ~Expr();
    virtual Expr* clone() const = 0;
    virtual void deleteChildren(){}
    virtual Expr* evaluate() = 0;
    static Expr* evaluateAndFree(Expr* n);
    static void deleteRecursive(Expr* n);
    static Expr* remove(std::vector<Expr*>& search, const Expr* pattern, Precedence prec = PREC_NONE);
    static Expr* remove(std::vector<Expr*>& search, const Expr* pattern, const std::vector<Expr*>::iterator& end, Precedence prec = PREC_NONE);
    virtual QString toMathBran(Precedence prec = PREC_NONE) const = 0;
    //virtual void writeMathBran(QTextStream& out) const = 0;
    virtual QString getKey(Precedence = PREC_NONE) const;
    ValueType valueType() const;
    virtual void visitChildren(Interpreter* interpreter) = 0;
    static bool isFalse(Expr* n);
    static bool isTrue(Expr* n);

protected:
    static Expr* searchForUndefined(const std::vector<Expr*>& args);
    template <Precedence prec = PREC_NONE> static bool compare(const Expr* a, const Expr* b){
        return a->getKey(prec) < b->getKey(prec);
    }
    static std::vector<Expr*> cloneArgs(const std::vector<Expr*> args);
};

const QString value_names[5] = {
    "SCALAR",
    "BOOLEAN",
    "MATRIX",
    "SET",
    "UNTYPED"
};

typedef std::vector<Expr*>::size_type vInt;
constexpr vInt vInt_MAX = std::numeric_limits<vInt>::max();

}

#endif // NODE_H
