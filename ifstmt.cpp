#include "ifstmt.h"

namespace Chelan {

IfStmt::IfStmt(Expr* condition, Stmt* body_true, Stmt* body_false)
    : Stmt(IF), condition(condition), body_true(body_true), body_false(body_false){

}

}
