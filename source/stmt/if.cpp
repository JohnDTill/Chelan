#include "if.h"

#include "expr.h"

namespace Chelan {

If::If(Expr* condition, Stmt* then, Stmt* el, std::vector<Expr*>::difference_type stack_size)
    : condition(condition), then(then), el(el), stack_size(stack_size) {}

void If::execute(Runtime& runtime){
    Expr* eval_condition = Expr::evaluateAndFree( condition->clone(), runtime );
    if(eval_condition->isDefinitivelyTrue()){
        delete eval_condition;
        then->execute(runtime);
    }else if(eval_condition->isDefinitivelyFalse()){
        delete eval_condition;
        el->execute(runtime);
    }else{
        Expr::deleteRecursive(eval_condition);
        runtime.out << "Runtime error: IF condition not evaluated to value";
        throw 1;
    }

    runtime.stack.erase(runtime.stack.end()-stack_size, runtime.stack.end());
}

}
