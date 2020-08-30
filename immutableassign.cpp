#include "immutableassign.h"

namespace Chelan {

ImmutableAssign::ImmutableAssign(Expr* expr)
    : Stmt(IMMUTABLE_ASSIGN), expr(expr) {

}

}
