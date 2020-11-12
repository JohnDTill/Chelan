#include "return.h"

#include <QDebug>

namespace Chelan {

Return::Return(Expr* e, std::vector<Expr*>::size_type stack_size)
    : e(e), stack_size(stack_size) {}

void Return::execute(Runtime& runtime){
    Expr* value = Expr::evaluateAndFree(e->clone(), runtime);
    runtime.stack.erase(runtime.stack.end()-static_cast<long long>(stack_size), runtime.stack.end());
    runtime.stack.push_back(value);
}

}
