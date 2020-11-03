#include "call.h"

#include "function.h"
#include "runtime.h"
#include "stmt.h"

namespace Chelan {

Call::Call()
    : Expr(CALL){}

Expr* Call::evaluate(Runtime& runtime){
    for(Expr* arg : args){
        runtime.stack.push_back( Expr::evaluateAndFree(arg->clone(), runtime) );
    }

    Expr* f_eval = Expr::evaluateAndFree( f->clone(), runtime );
    Q_ASSERT(dynamic_cast<Function*>(f_eval));
    static_cast<Function*>(f_eval)->body->execute(runtime);
    //DO THIS - error handling is flawed

    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++){
        Expr::deleteRecursive( runtime.stack.back() );
        runtime.stack.pop_back();
    }

    return runtime.stack.back();
}

}
