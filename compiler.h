#ifndef COMPILER_H
#define COMPILER_H

#include <QMap>
#include <vector>

namespace Neb{
    class Node;
}

namespace Chelan {

class Stmt;
class Expr;

class Compiler{
public:
    std::vector<Chelan::Stmt*> stmts;
    bool had_error;

private:
    std::vector<Neb::Node*> parse_forest;
    std::vector<QMap<QString, uint> > scopes; //Maps id to stack slot

public:
    Compiler(std::vector<Neb::Node*>& parse_forest);
    bool compileAll();

private:
    Stmt* compileStmt(Neb::Node* parse_tree);
    Expr* compileExpr(Neb::Node* parse_tree);
};

}

#endif // COMPILER_H
