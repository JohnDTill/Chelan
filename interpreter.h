#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QString>
#include <vector>

namespace Chelan{

class Stmt;
class Expr;

class Interpreter{

std::vector<Stmt*> stmts;
std::vector<Expr*> stack;
QString output;
QString err_msg;

public:
    Interpreter(std::vector<Stmt*> stmts);
    QString interpret();
    Expr* evaluate(Expr* expr);

private:
    bool interpret(Stmt* stmt);
};

}

#endif // INTERPRETER_H
