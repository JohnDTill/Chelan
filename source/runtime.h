#ifndef RUNTIME_H
#define RUNTIME_H

#include <QTextStream>

namespace Chelan {

class Expr;

class Runtime{
public:
    QTextStream out;
    std::vector<Expr*> stack;
    bool allow_imaginary_values = false;

    Runtime(QString& out_str) : out(&out_str){}

    QString toMathBran() const;
};

}

#endif // RUNTIME_H
