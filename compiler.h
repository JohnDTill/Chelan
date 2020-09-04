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
    std::vector<Stmt*> stmts;
    QString err_msg;

private:
    std::vector<Neb::Node*> parse_forest;
    typedef std::tuple<std::vector<void*>::size_type, bool, ValueType> SymTableInfo;
    typedef QMap<QString, SymTableInfo> SymTable;
    typedef std::vector<SymTable> ScopeChain;
    ScopeChain scopes; //Maps id to stack slot
    std::vector<void*>::size_type stack_slot;

    std::vector<Stmt*> all_stmts;
    std::vector<Expr*> all_exprs;
    std::vector<ValueType> vt;

public:
    Compiler(std::vector<Neb::Node*>& parse_forest);
    bool compileAll();

private:
    Stmt* pushStmt(Neb::Node* parse_tree);
    Expr* pushExpr(Neb::Node* parse_tree);
    Stmt* compileStmt(Neb::Node* parse_tree);
    Expr* compileExpr(Neb::Node* parse_tree);
    std::vector<Expr*> pushExpr(std::vector<Neb::Node*>& parse_forest);
    Stmt* assign(Neb::Node* stmt);
    Stmt* ifStmt(Neb::Node* stmt);
    Stmt* block(Neb::Node* stmt);
    Expr* matrix(Neb::Node* expr);
    Expr* number(Neb::Node* expr);
    Expr* read(Neb::Node* expr);
};

}

#endif // COMPILER_H
