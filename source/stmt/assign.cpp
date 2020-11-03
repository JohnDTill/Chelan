#include "assign.h"

#include "expr.h"

namespace Chelan {

Assign::Assign(std::vector<Expr*>::size_type offset, Expr* rhs)
    : offset(offset), rhs(rhs) {}

bool Assign::execute(Runtime& runtime){
    Q_ASSERT(runtime.stack.size() >= offset);
    runtime.stack[runtime.stack.size() - offset] = Expr::evaluateAndFree( rhs->clone(), runtime );
    return false;
}

}
