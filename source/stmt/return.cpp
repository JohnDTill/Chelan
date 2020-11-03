#include "return.h"

namespace Chelan {

Return::Return(Expr* e)
    : e(e) {}

bool Return::execute(Runtime& runtime){
    runtime.stack.push_back( Expr::evaluateAndFree(e->clone(), runtime) );
    return false;
}

}
