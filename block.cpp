#include "block.h"

namespace Chelan {

Block::Block(std::vector<Stmt*>& stmts, std::vector<Expr*>::size_type stack_size)
    : Stmt(BLOCK), stmts(stmts), stack_size(stack_size) {

}

}
