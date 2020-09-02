#include "untypedaddition.h"

#include "chelan.h"

namespace Chelan{

UntypedAddition::UntypedAddition(const std::vector<Expr*>& args)
    : Expr(UNTYPED_ADDITION), args(args) {
    //DO THIS
}

Expr* UntypedAddition::clone() const{
    return new UntypedAddition(cloneArgs(args));
}

Expr* UntypedAddition::evaluate(){
    //MOVED
    return nullptr;
}

QString UntypedAddition::toMathBran(Expr::Precedence) const{
    QString str = args.front()->toMathBran(PREC_ADDITION);
    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++)
        str += " + " + args[i]->toMathBran(PREC_ADDITION);

    return str;
}

void UntypedAddition::visitChildren(Interpreter* interpreter){
    for(std::vector<Expr*>::size_type i = 0; i < args.size(); i++)
        args[i] = interpreter->evaluate(args[i]);
}

Expr* UntypedAddition::evaluate(QString& err_msg){
    ValueType candidate = args.front()->valueType();
    bool deduction_failed = (candidate == UNTYPED);

    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++){
        ValueType vt = args[i]->valueType();
        if(vt == UNTYPED) deduction_failed = true;
        else if(vt != candidate && candidate != UNTYPED){
            err_msg += "TYPE ERROR: Cannot add type " + value_names[vt]
                    + " with type " + value_names[candidate] + '\n';
            return new Undefined("", true);
        }else candidate = vt;
    }

    if(deduction_failed) return nullptr;

    switch(candidate){
        case SCALAR: return new ScalarAddition(args);
        case MATRIX: return new MatrixAddition(args);
        default:
            err_msg += "TYPE ERROR: Type " + value_names[candidate] + " cannot be added\n";
            return new Undefined("", true);
    }
}

}
