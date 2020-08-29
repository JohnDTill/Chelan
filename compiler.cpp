#include "compiler.h"

#include <neb_node.h>

namespace Chelan {

Compiler::Compiler(std::vector<Neb::Node*>& parse_forest)
    : parse_forest(parse_forest){

}

bool Compiler::compileAll(){
    had_error = false;

    for(Neb::Node* parse_tree : parse_forest){
        stmts.push_back(compileStmt(parse_tree));
        Neb::Node::deletePostorder(parse_tree);
    }

    return had_error;
}

Stmt* Compiler::compileStmt(Neb::Node* parse_tree){
    //DO THIS
    return nullptr;
}

Expr* Compiler::compileExpr(Neb::Node* parse_tree){
    //DO THIS
    return nullptr;
}

}
