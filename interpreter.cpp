#include "interpreter.h"

#include "chelan.h"

namespace Chelan {

Interpreter::Interpreter(std::vector<Stmt*> stmts)
    : stmts(stmts) {
    //Initialize predefined values
    stack.push_back(new Pi());
}

QString Interpreter::interpret(){
    for(Stmt* stmt : stmts) if(!interpret(stmt)) break;

    //Free stack memory
    for(Expr* expr : stack) Expr::deleteRecursive(expr);

    return output + err_msg;
}

bool Interpreter::interpret(Stmt* stmt){
    switch (stmt->type) {
        case BLOCK:
            for(Stmt* st : static_cast<Block*>(stmt)->stmts)
                if(!interpret(st)) return false;
            return true;
        case IF:{
            IfStmt* if_stmt = static_cast<IfStmt*>(stmt);
            Expr* condition = evaluate(if_stmt->condition->clone());
            if(Expr::isTrue(condition)){
                delete condition;
                return interpret(if_stmt->body_true);
            }else if(!Expr::isFalse(condition)){
                err_msg += "IF condition not evaluated to a constant: " + condition->toMathBran() + '\n';
                Expr::deleteRecursive(condition);
                return false;
            }else if(if_stmt->body_false){
                delete condition;
                return interpret(if_stmt->body_false);
            }
        }
        case IMMUTABLE_ASSIGN:
            stack.push_back( evaluate(static_cast<ImmutableAssign*>(stmt)->expr->clone()) );
            return true;
        case PRINT:{
            Expr* to_print = evaluate(static_cast<Print*>(stmt)->expr->clone());
            if(!err_msg.isEmpty()) return false;
            output += to_print->toMathBran() + '\n';
            Expr::deleteRecursive(to_print);
            return true;
        }
    }
}

Expr* Interpreter::evaluate(Expr* expr){
    switch (expr->type) {
        case MATRIX_ADDITION:{
            expr->visitChildren(this);
            MatrixAddition* a = static_cast<MatrixAddition*>(expr);

            //Fast path//
            //Fold constants
            for(std::vector<Expr*>::size_type i = a->args.size()-1; i < a->args.size(); i--){
                if(a->args[i]->type == MATRIX_NUMERIC){
                    std::vector<Expr*>& es = static_cast<MatrixNumeric*>(a->args[i])->args;
                    std::vector<Expr*>::size_type rows = static_cast<MatrixNumeric*>(a->args[i])->rows;
                    std::vector<Expr*>::size_type cols = static_cast<MatrixNumeric*>(a->args[i])->cols;
                    std::vector<mpq_class> vals(es.size());
                    for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++){
                        vals[k] = static_cast<Rational*>(es[k])->value;
                        delete es[k];
                    }
                    delete a->args[i];
                    a->args.erase(a->args.begin()+i);

                    for(std::vector<Expr*>::size_type j = i-1; j < a->args.size(); j--){
                        if(a->args[j]->type == MATRIX_NUMERIC){
                            if(static_cast<MatrixNumeric*>(a->args[j])->rows != rows ||
                               static_cast<MatrixNumeric*>(a->args[j])->cols != cols){
                                err_msg += "SIZE ERROR: Added matrices of incompatible sizes "
                                        + QString::number(static_cast<MatrixNumeric*>(a->args[j])->rows)
                                        + "×"
                                        + QString::number(static_cast<MatrixNumeric*>(a->args[j])->cols)
                                        + " and "
                                        + QString::number(rows) + "×" + QString::number(cols)
                                        + "\n";
                                return new Undefined("", true);
                            }

                            std::vector<Expr*>& es = static_cast<MatrixNumeric*>(a->args[j])->args;
                            for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++){
                                vals[k] += static_cast<Rational*>(es[k])->value;
                                delete es[k];
                            }
                            delete a->args[j];
                            a->args.erase(a->args.begin()+j);
                        }
                    }

                    std::vector<Expr*> ex(vals.size());
                    for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++)
                        ex[k] = new Rational(vals[k]);

                    a->args.push_back(new MatrixNumeric(rows, cols, ex));

                    break;
                }
            }
            if(a->args.size()==1) return a->args[0];

            //Symbolic//
            return expr;
        }
        case READ:
            Q_ASSERT(static_cast<Read*>(expr)->slot < stack.size());
            return evaluate(stack[static_cast<Read*>(expr)->slot]->clone());
        case UNTYPED_ADDITION:{
            expr->visitChildren(this);
            if(Expr* e = static_cast<UntypedAddition*>(expr)->evaluate(err_msg)){
                delete expr;
                return e;
            }else{
                return expr;
            }
        }
        default:
            expr->visitChildren(this);
            return Expr::evaluateAndFree(expr);
    }
}

}
