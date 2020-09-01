#include "block.h"

namespace Chelan {

Block::Block(std::vector<Stmt*>& stmts)
    : Stmt(BLOCK), stmts(stmts) {

}

}
