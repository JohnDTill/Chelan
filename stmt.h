#ifndef STMT_H
#define STMT_H

#include "stmttype.h"

namespace Chelan {

class Expr;

class Stmt{
public:
    const StmtType type;

public:
    Stmt(const StmtType& type);
};

}

#endif // STMT_H
