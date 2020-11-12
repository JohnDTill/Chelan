#ifndef BLOCK_H
#define BLOCK_H

#include "../stmt.h"

namespace Chelan {

class Block : public Stmt{
private:
    std::vector<Stmt*> stmts;

public:
    Block(const std::vector<Stmt*>& stmts);
    void execute(Runtime& runtime) override final;
};

}

#endif // BLOCK_H
