#include "while.h"

#include "expr.h"

namespace Chelan {

While::While(Expr* condition, Stmt* body)
    : condition(condition), body(body) {}

bool While::execute(Runtime& runtime){
    Expr* eval_condition = Expr::evaluateAndFree( condition->clone(), runtime );

    while(eval_condition->isDefinitivelyTrue()){
        delete eval_condition;
        if(body->execute(runtime)) return true;
        eval_condition = Expr::evaluateAndFree( condition->clone(), runtime );
    }

    if(eval_condition->isDefinitivelyFalse()){
        delete eval_condition;
        return false;
    }else{
        Expr::deleteRecursive(eval_condition);
        runtime.out << "Runtime error: WHILE condition not evaluated to value";
        return true;
    }
}

}
