#include "absolutevalue.h"

#include "chelan.h"

namespace Chelan{

AbsoluteValue::AbsoluteValue(Expr* e)
    : Expr(ABSOLUTE_VALUE), e(e) {}

Expr* AbsoluteValue::clone() const{
    return new AbsoluteValue(e->clone());
}

Expr* AbsoluteValue::evaluate(Runtime& runtime){
    e = evaluateAndFree(e, runtime);

    switch (e->type) {
        case RATIONAL:{
            Rational* rat = static_cast<Rational*>(e);
            if(rat->value < 0){
                mpq_class val = -rat->value;
                delete rat;
                return new Rational(val);
            }else{
                return rat;
            }
        }
        default: return nullptr;
    }
}

void AbsoluteValue::writeMathBran(QTextStream& out, Precedence) const{
    out << '|';
    e->writeMathBran(out);
    out << '|';
}

}
