#include "if.h"

#include "expr.h"

namespace Chelan {

If::If(Expr* condition, Stmt* then, Stmt* el)
    : condition(condition), then(then), el(el) {}

bool If::execute(Runtime& runtime){
    Expr* eval_condition = Expr::evaluateAndFree( condition->clone(), runtime );
    if(eval_condition->isDefinitivelyTrue()){
        delete eval_condition;
        return then->execute(runtime);
    }else if(eval_condition->isDefinitivelyFalse()){
        delete eval_condition;
        return el ? el->execute(runtime) : false;
    }

    Expr::deleteRecursive(eval_condition);
    runtime.out << "Runtime error: IF condition not evaluated to value";
    return true;
}

}
