#include "block.h"

namespace Chelan {

Block::Block(std::vector<Expr*>::size_type stack_size, const std::vector<Stmt*>& stmts)
    : stack_size(stack_size), stmts(stmts) {}

bool Block::execute(Runtime& runtime){
    //DO THIS - allow return stmt to abort
    for(Stmt* stmt : stmts)
        if(stmt->execute(runtime)) return true;
    return false;
}

}
