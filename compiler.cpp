#include "compiler.h"

#include <neb_node.h>
#include "chelan.h"

namespace Chelan {

Compiler::Compiler(std::vector<Neb::Node*>& parse_forest)
    : parse_forest(parse_forest){
    //Add predefined variables
    scopes.push_back(SymTable());
    scopes[0]["π"] = std::make_pair(0, true);
    stack_slot = 1;

    //Add global scope
    scopes.push_back(SymTable());
}

bool Compiler::compileAll(){
    for(Neb::Node* parse_tree : parse_forest){
        stmts.push_back(compileStmt(parse_tree));
        Neb::Node::deletePostorder(parse_tree);
    }

    return err_msg.isEmpty();
}

Stmt* Compiler::compileStmt(Neb::Node* parse_tree){
    switch (parse_tree->type) {
        case Neb::EQUAL: return assign(parse_tree);
        case Neb::PRINT: return new Print(compileExpr(parse_tree->children[0]));
        default:
            err_msg += "ERROR: unrecognized Neb::Node stmt";
            return nullptr;
    }
}

Expr* Compiler::compileExpr(Neb::Node* parse_tree){    
    switch(parse_tree->type){
        case Neb::ADDITION: return new UntypedAddition(compileExprs(parse_tree->children));
        case Neb::DIVIDE: return ScalarMultiplication::Divide(compileExpr(parse_tree->children[0]), compileExpr(parse_tree->children[1]));
        case Neb::FALSE: return new Boolean(false);
        case Neb::FRACTION: return ScalarMultiplication::Divide(compileExpr(parse_tree->children[0]), compileExpr(parse_tree->children[1]));
        case Neb::GROUP_PAREN: return compileExpr(parse_tree->children[0]);
        case Neb::GROUP_BRACKET: return compileExpr(parse_tree->children[0]);
        case Neb::IDENTIFIER: return read(parse_tree);
        case Neb::LOGICAL_NOT: return Negation::Not(compileExpr(parse_tree->children[0]));
        case Neb::LOGICAL_OR: return Disjunction::Or(compileExpr(parse_tree->children[0]), compileExpr(parse_tree->children[1]));
        case Neb::LOGICAL_AND: return Conjunction::And(compileExpr(parse_tree->children[0]), compileExpr(parse_tree->children[1]));
        case Neb::NUMBER: return number(parse_tree);
        case Neb::MATRIX: return matrix(parse_tree);
        case Neb::TRUE: return new Boolean(true);

        //FIX THESE
            /*
        case Neb::SUBTRACTION:
            return Chelan::Subtract(convertToAst(n->children[0]), convertToAst(n->children[1]));
        case Neb::UNARY_MINUS:
            return Chelan::Multiply(-1, convertToAst(n->children[0]));
        case Neb::MULTIPLICATION:
        case Neb::IMPLICIT_MULTIPLY:
            return Chelan::Multiply(convertToAst(n->children[0]), convertToAst(n->children[1]));
        case Neb::DOT:
            return Chelan::Multiply(convertToAst(n->children[0]), convertToAst(n->children[1]));
        case Neb::CROSS:
            return Chelan::Multiply(convertToAst(n->children[0]), convertToAst(n->children[1]));

        case Neb::FORWARDSLASH:
        case Neb::BACKSLASH:
            return Chelan::Divide(convertToAst(n->children[1]), convertToAst(n->children[0]));
        case Neb::POWER:
            return Chelan::Raise(convertToAst(n->children[0]), convertToAst(n->children[1]));
        case Neb::CASES:
            if(n->children.size()==4){
                return Chelan::Ternary(convertToAst(n->children[1]),
                        convertToAst(n->children[0]),
                        convertToAst(n->children[2]));
            }else{
                return new Chelan::Undefined("ERROR: only ternary \"" + n->data + "\" cases are supported");
            }
        case Neb::LESS:
            return Chelan::IsLess(convertToAst(n->children[0]), convertToAst(n->children[1]));
        case Neb::EQUAL:
            return Chelan::IsEqual(convertToAst(n->children[0]), convertToAst(n->children[1]));
        //FIX THESE
        */

        default:
            err_msg += "ERROR: unrecognized Neb::Node expr";
            return nullptr;
    }
}

std::vector<Expr*> Compiler::compileExprs(std::vector<Neb::Node*>& parse_forest){
    std::vector<Expr*> exprs;
    for(Neb::Node* parse_tree : parse_forest) exprs.push_back(compileExpr(parse_tree));

    return exprs;
}

Stmt* Compiler::assign(Neb::Node* stmt){
    Q_ASSERT(stmt->type == Neb::EQUAL);

    if(stmt->children.size() != 2){
        err_msg += "ERROR: assignment statement can have only one '=' symbol\n";
        return nullptr;
    }
    Neb::Node* lhs = stmt->children[0];
    Expr* rhs = compileExpr(stmt->children[1]);

    QString id = lhs->data;
    if(scopes.back().contains(id)){
        err_msg += "ERROR: variable \"" + id + "\" has already been defined";
        return nullptr;
    }

    scopes.back()[id] = std::make_pair(stack_slot++, true);

    return new ImmutableAssign(rhs);
}

Expr* Compiler::matrix(Neb::Node* expr){
    Q_ASSERT(expr->children.size() >= 3);
    uint rows = expr->children[0]->data.toUInt();
    uint cols = expr->children[1]->data.toUInt();
    Q_ASSERT(expr->children.size() == 2+rows*cols);
    std::vector<Chelan::Expr*> children(rows*cols);
    for(uint i = 0; i < rows*cols; i++)
        children.push_back(compileExpr(expr->children[2+i]));
    return new Chelan::Matrix(rows,cols,children);
}

Expr* Compiler::number(Neb::Node* expr){
    Q_ASSERT(expr->type == Neb::NUMBER);

    auto split = expr->data.splitRef('.');

    if(split.size() == 1){
        return new Rational(expr->data);
    }else{
        Q_ASSERT(split.size() == 2);
        mpz_class num((split[0] + split[1]).toStdString());
        mpz_class den('1' + std::string(split[1].size(), '0'));

        return new Rational(mpq_class(num,den));
    }
}

Expr* Compiler::read(Neb::Node* expr){
    Q_ASSERT(expr->type == Neb::IDENTIFIER);

    for(ScopeChain::reverse_iterator i = scopes.rbegin(); i != scopes.rend(); i++){
        auto lookup = i->constFind(expr->data);
        if(lookup != i->constEnd()){
            return new Read(lookup.value().first);
        }
    }

    err_msg += "ERROR: variable \"" + expr->data + "\" is not defined";
    return nullptr;
}

}
