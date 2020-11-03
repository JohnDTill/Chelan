#ifndef RUNTIME_H
#define RUNTIME_H

#include <QTextStream>

namespace Chelan {

class Expr;

class Runtime{
public:
    QTextStream out;
    std::vector<Expr*> stack;

    Runtime(QString& out_str) : out(&out_str){}
};

}

#endif // RUNTIME_H
