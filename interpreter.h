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

public:
    Interpreter(std::vector<Stmt*> stmts);
    QString interpret();
};

}

#endif // INTERPRETER_H
