#ifndef STMT_H
#define STMT_H

#include <QTextStream>

namespace Chelan {

struct Runtime{
    QTextStream out;

    Runtime(QString& out_str) : out(&out_str){}
};

class Stmt{
public:
    virtual bool execute(Runtime& runtime) = 0;
};

}

#endif // STMT_H
