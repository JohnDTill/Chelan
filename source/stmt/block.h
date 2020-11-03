#ifndef BLOCK_H
#define BLOCK_H

#include "../stmt.h"

namespace Chelan {

class Block : public Stmt{
private:
    std::vector<Expr*>::size_type stack_size;
    std::vector<Stmt*> stmts;

public:
    Block(std::vector<Expr*>::size_type stack_size, const std::vector<Stmt*>& stmts);
    bool execute(Runtime& runtime) override final;
};

}

#endif // BLOCK_H
