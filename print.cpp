#include "print.h"

namespace Chelan {

Print::Print(Chelan::Expr* expr)
    : Stmt(PRINT), expr(expr) {

}

}
