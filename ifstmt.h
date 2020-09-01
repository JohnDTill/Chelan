#ifndef IFSTMT_H
#define IFSTMT_H

#include "stmt.h"

namespace Chelan {

class IfStmt : public Stmt{
public:
    Expr* condition;
    Stmt* body_true;
    Stmt* body_false;

public:
    IfStmt(Expr* condition, Stmt* body_true, Stmt* body_false = nullptr);
};

}

#endif // IFSTMT_H
