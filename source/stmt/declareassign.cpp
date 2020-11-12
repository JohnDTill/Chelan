#include "declareassign.h"

#include "expr.h"

#include <QDebug>

namespace Chelan {

DeclareAssign::DeclareAssign(Expr* rhs)
    : rhs(rhs){}

void DeclareAssign::execute(Runtime& runtime){
    runtime.stack.push_back( Expr::evaluateAndFree(rhs->clone(), runtime) );
}

}
