#include "block.h"

#include "chelan.h"

namespace Chelan {

Block::Block(std::vector<Stmt*>& stmts, std::vector<Expr*>::size_type stack_size)
    : Stmt(BLOCK), stmts(stmts), stack_size(stack_size) {

}

uint32_t Block::writeDOT(QTextStream& out, uint64_t& curr) const{
    uint64_t id = curr++;

    out << "\tn" << QString::number(id) << "[label=\"BLOCK";
    //Type info here
    out << '"';
    out << "]\n";

    for(Stmt* stmt : stmts){
        //uint64_t child_id = stmt->writeDOT(out, curr);
        //out << "\tn" << QString::number(id) << "->n" << QString::number(child_id) << '\n';
    }

    return id;
}

}
