#ifndef COMPILER_H
#define COMPILER_H

#include <QMap>
#include <vector>

#include "neb_node.h"
#include "expr.h"

namespace Chelan {

class Stmt;
class Expr;

class Compiler{
public:
    std::vector<Chelan::Stmt*> stmts;
    QString err_msg;

private:
    std::vector<Neb::Node*> parse_forest;
    typedef std::tuple<std::vector<void*>::size_type, bool, ValueType> SymTableInfo;
    typedef QMap<QString, SymTableInfo> SymTable;
    typedef std::vector<SymTable> ScopeChain;
    ScopeChain scopes; //Maps id to stack slot
    std::vector<void*>::size_type stack_slot;

public:
    Compiler(std::vector<Neb::Node*>& parse_forest);
    bool compileAll();

private:
    Stmt* compileStmt(Neb::Node* parse_tree);
    Expr* compileExpr(Neb::Node* parse_tree);
    std::vector<Expr*> compileExprs(std::vector<Neb::Node*>& parse_forest);
    Stmt* assign(Neb::Node* stmt);
    Expr* matrix(Neb::Node* expr);
    Expr* number(Neb::Node* expr);
    Expr* read(Neb::Node* expr);
};

}

#endif // COMPILER_H
