#ifndef BLOCK_H
#define BLOCK_H

#include "stmt.h"
#include <vector>

namespace Chelan {

class Block : public Stmt{
public:
    std::vector<Stmt*> stmts;
    std::vector<Expr*>::size_type stack_size;

public:
    Block(std::vector<Stmt*>& stmts, std::vector<Expr*>::size_type stack_size);
};

}

#endif // BLOCK_H
