#include "while.h"

#include "expr.h"

namespace Chelan {

While::While(Expr* condition, Stmt* body, std::vector<Expr*>::difference_type stack_size)
    : condition(condition), body(body), stack_size(stack_size) {}

void While::execute(Runtime& runtime){
    Expr* eval_condition = Expr::evaluateAndFree( condition->clone(), runtime );

    while(eval_condition->isDefinitivelyTrue()){
        delete eval_condition;
        body->execute(runtime);
        runtime.stack.erase(runtime.stack.end()-stack_size, runtime.stack.end());
        eval_condition = Expr::evaluateAndFree( condition->clone(), runtime );
    }

    if(eval_condition->isDefinitivelyFalse()){
        delete eval_condition;
    }else{
        runtime.out << "Runtime error: WHILE condition not evaluated to value: " << eval_condition->toMathBran();
        Expr::deleteRecursive(eval_condition);
        throw 1;
    }
}

}
