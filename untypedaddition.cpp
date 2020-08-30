#include "untypedaddition.h"

#include "chelan.h"

namespace Chelan{

UntypedAddition::UntypedAddition(const std::vector<Expr*>& args)
    : Expr(UNTYPED_ADDITION), args(args) {
    //DO THIS
}

Expr* UntypedAddition::clone() const{
    return new UntypedAddition(args);
}

Expr* UntypedAddition::evaluate(){
    ValueType candidate = args.front()->valueType();
    if(candidate == UNTYPED) return nullptr;
    bool deduction_failed = false;

    for(std::vector<Expr*>::size_type i = 1; i < args.size(); i++){
        ValueType vt = args[i]->valueType();
        if(vt == UNTYPED) deduction_failed = true;
        else if(vt != candidate){
            return new Undefined("ERROR: Cannot add type " + value_names[vt]
                                 + " with type " + value_names[candidate],
                                 true);
        }
    }

    if(deduction_failed) return nullptr;

    switch(candidate){
        case SCALAR: return new ScalarAddition(args);
        case MATRIX: return new MatrixAddition(args);
        default: return new Undefined("ERROR: Type " +
                                      value_names[candidate] + " cannot be added",
                                      true);
    }
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

}
