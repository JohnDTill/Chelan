#include "interpreter.h"

namespace Chelan {

Interpreter::Interpreter(std::vector<Stmt*> stmts)
    : stmts(stmts) {

}

QString Interpreter::interpret(){
    for(Stmt* stmt : stmts){

    }

    return output;
}

}
