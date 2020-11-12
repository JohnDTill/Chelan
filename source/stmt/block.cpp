#include "block.h"

namespace Chelan {

Block::Block(const std::vector<Stmt*>& stmts)
    : stmts(stmts) {}

void Block::execute(Runtime& runtime){
    for(Stmt* stmt : stmts) stmt->execute(runtime);
}

}
