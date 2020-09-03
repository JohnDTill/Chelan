#include "untypedmultiplication.h"

#include "chelan.h"

namespace Chelan{

UntypedMultiplication::UntypedMultiplication(const std::vector<Expr*>& args)
    : Expr(UNTYPED_MULTIPLICATION), args(args) {}

Expr* UntypedMultiplication::clone() const{
    return new UntypedMultiplication(cloneArgs(args));
}

Expr* UntypedMultiplication::evaluate(){
    //MOVED
    return nullptr;
}

QString UntypedMultiplication::toMathBran(Expr::Precedence) const{
    QString str = args.front()->toMathBran(PREC_ADDITION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        str += '*' + args[i]->toMathBran(PREC_ADDITION);

    return str;
}

void UntypedMultiplication::visitChildren(Interpreter* interpreter){
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        args[i] = interpreter->evaluate(args[i]);
}

Expr* UntypedMultiplication::evaluate(QString& err_msg){
    std::vector<Expr*> matrices;
    std::vector<Expr*> scalars;

    for(Expr* expr : args){
        switch (expr->valueType()) {
            case MATRIX: matrices.push_back(expr); break;
            case SCALAR: scalars.push_back(expr); break;
            case UNTYPED: break;
            default:
                err_msg += "TYPE ERROR: Cannot multiply type " + value_names[expr->valueType()] + '\n';
                return new Undefined("", true);
        }
    }

    if(matrices.size() + scalars.size() != args.size()) return nullptr;
    else if(scalars.size() == args.size()) return new ScalarMultiplication(args);
    else return new MatrixMultiplication(matrices, new ScalarMultiplication(scalars));
}

}
