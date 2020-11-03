#include "print.h"

namespace Chelan {

Print::Print(Chelan::Expr* e)
    : e(e){}

bool Print::execute(Runtime& runtime){
    Expr* result = Expr::evaluateAndFree(e->clone(), runtime);
    runtime.out << result->toMathBran() << '\n';
    Expr::deleteRecursive(result);

    return false;
}

}
