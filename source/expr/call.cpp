#include "call.h"

#include <chelan.h>

namespace Chelan {

Call::Call(Expr* f, std::vector<Expr*> args, bool has_return_value)
    : Expr(CALL), f(f), args(args), has_return_value(has_return_value) {}

Expr* Call::clone() const{
    return new Call(f->clone(), cloneArgs(args), has_return_value);
}

Expr* Call::evaluate(Runtime& runtime){
    Expr* f_eval = Expr::evaluateAndFree( f->clone(), runtime );
    Q_ASSERT(dynamic_cast<Function*>(f_eval));

    for(Expr* arg : args)
        runtime.stack.push_back( Expr::evaluateAndFree(arg->clone(), runtime) );

    static_cast<Function*>(f_eval)->body->execute(runtime);

    Expr* return_value = runtime.stack.back();
    runtime.stack.pop_back();

    Expr::deleteRecursive(f_eval);

    return return_value;
}

void Call::writeMathBran(QTextStream& out, Precedence prec) const{
    f->writeMathBran(out);
    out << '(';
    if(args.size()) args.front()->writeMathBran(out);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++){
        out << ", ";
        args.at(i)->writeMathBran(out);
    }
    out << ')';
}

}
