#include "interpreter.h"

#include "chelan.h"

namespace Chelan {

Interpreter::Interpreter(std::vector<Stmt*> stmts)
    : stmts(stmts) {
    //Initialize predefined values
    stack.push_back(new Pi());
}

QString Interpreter::interpret(){
    for(Stmt* stmt : stmts) if(!interpret(stmt)) break;

    //Free stack memory
    for(Expr* expr : stack) Expr::deleteRecursive(expr);

    return output;
}

bool Interpreter::interpret(Stmt* stmt){
    switch (stmt->type) {
        case IMMUTABLE_ASSIGN:
            stack.push_back( evaluate(static_cast<ImmutableAssign*>(stmt)->expr->clone()) );
            return true;
        case PRINT:{
            Expr* to_print = evaluate(static_cast<Print*>(stmt)->expr->clone());
            output += to_print->toMathBran();
            Expr::deleteRecursive(to_print);
            return true;
        }
    }
}

Expr* Interpreter::evaluate(Expr* expr){
    switch (expr->type) {
        case READ:
            Q_ASSERT(static_cast<Read*>(expr)->slot < stack.size());
            return evaluate(stack[static_cast<Read*>(expr)->slot]->clone());
        default:
            expr->visitChildren(this);
            return Expr::evaluateAndFree(expr);
    }
}

}
