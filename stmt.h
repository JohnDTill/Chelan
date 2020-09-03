#ifndef STMT_H
#define STMT_H

#include "stmttype.h"
class QTextStream;

namespace Chelan {

class Expr;

class Stmt{
public:
    const StmtType type;

public:
    Stmt(const StmtType& type);
    //virtual uint32_t writeDOT(QTextStream& out, uint64_t& curr) const = 0;
};

}

#endif // STMT_H
