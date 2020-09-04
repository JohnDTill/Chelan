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
        case BLOCK:{
            Block* b = static_cast<Block*>(stmt);
            for(Stmt* st : b->stmts)
                if(!interpret(st)) return false;
            for(std::vector<Expr*>::size_type i = 0; i < b->stack_size; i++){
                Expr::deleteRecursive(stack.back());
                stack.pop_back();
            }
            return true;
        }
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
            }else{
                return true;
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
    if(!err_msg.isEmpty()) return expr;

    switch (expr->type) {
        case MATRIX_ADDITION: return matrixAddition(expr);
        case MATRIX_MULTIPLICATION: return matrixMultiplication(expr);
        case READ: return read(expr);
        case UNTYPED_ADDITION:{
            expr->visitChildren(this);
            if(Expr* e = static_cast<UntypedAddition*>(expr)->evaluate(err_msg))
                expr = evaluate(e);
            return expr;
        }
        case UNTYPED_MULTIPLICATION:{
            expr->visitChildren(this);
            if(Expr* e = static_cast<UntypedMultiplication*>(expr)->evaluate(err_msg))
                expr = evaluate(e);
            return expr;
        }
        case UNTYPED_POWER:{
            expr->visitChildren(this);
            if(Expr* e = static_cast<UntypedPower*>(expr)->evaluate(err_msg))
                expr = evaluate(e);
            return expr;
        }
        default:
            expr->visitChildren(this);
            while(Expr* e = expr->evaluate()) expr = e;
            return expr;
    }
}

Expr* Interpreter::matrixAddition(Expr* expr){
    Q_ASSERT(expr->type == MATRIX_ADDITION);

    expr->visitChildren(this);
    MatrixAddition* a = static_cast<MatrixAddition*>(expr);

    //Fast path//
    //Fold constants
    for(std::vector<Expr*>::size_type i = a->args.size()-1; i < a->args.size(); i--){
        if(a->args[i]->type == MATRIX_NUMERIC){
            std::vector<mpq_class> vals = static_cast<MatrixNumeric*>(a->args[i])->args;
            std::vector<mpq_class>::size_type rows = static_cast<MatrixNumeric*>(a->args[i])->rows;
            std::vector<mpq_class>::size_type cols = static_cast<MatrixNumeric*>(a->args[i])->cols;
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

                    std::vector<mpq_class>& es = static_cast<MatrixNumeric*>(a->args[j])->args;
                    for(std::vector<Expr*>::size_type k = 0; k < vals.size(); k++)
                        vals[k] += es[k];
                    delete a->args[j];
                    a->args.erase(a->args.begin()+j);
                }
            }

            a->args.push_back(new MatrixNumeric(rows, cols, vals));

            break;
        }
    }
    if(a->args.size()==1) return a->args[0];

    //Symbolic//
    return expr;
}

Expr* Interpreter::matrixMultiplication(Expr* expr){
    Q_ASSERT(expr->type == MATRIX_MULTIPLICATION);

    expr->visitChildren(this);
    MatrixMultiplication* a = static_cast<MatrixMultiplication*>(expr);

    //Fast path//
    //Fold constants
    for(std::vector<Expr*>::size_type i = a->args.size()-1; i < a->args.size(); i--){
        if(a->args[i]->vt == SCALAR){
            a->scaling = new ScalarMultiplication({a->scaling, a->args[i]});
            a->args.erase(a->args.begin() + i);
        }

        if(i > 0 && a->args[i]->type == MATRIX_NUMERIC && a->args[i-1]->type == MATRIX_NUMERIC){
            MatrixNumeric* A = static_cast<MatrixNumeric*>(a->args[i-1]);
            MatrixNumeric* B = static_cast<MatrixNumeric*>(a->args[i]);

            if(A->cols != B->rows){
                err_msg += "SIZE ERROR: Multiplied matrices of incompatible sizes "
                        + QString::number(A->rows) + "×" + QString::number(A->cols)
                        + " and "
                        + QString::number(B->rows) + "×" + QString::number(B->cols)
                        + "\n";
                return new Undefined("", true);
            }

            std::vector<mpq_class> vals(A->rows * B->cols);

            for(std::vector<mpq_class>::size_type i = 0; i < A->rows; i++){
                for(std::vector<mpq_class>::size_type j = 0; j < B->cols; j++){
                    std::vector<mpq_class>::size_type index = i*B->cols + j;
                    vals[index] = A->at(i,0)*B->at(0,j);
                    for(std::vector<mpq_class>::size_type k = 1; k < A->cols; k++)
                        vals[index] += A->at(i,k)*B->at(k,j);
                }
            }

            a->args[i-1] = new MatrixNumeric(A->rows, B->cols, vals);
            delete A;
            delete B;
            a->args.erase(a->args.begin() + i);
        }
    }

    if(a->args.size()==1 && a->args[0]->type == MATRIX_NUMERIC && a->scaling->type == RATIONAL){
        mpq_class scaling = static_cast<Rational*>(a->scaling)->value;
        for(mpq_class& val : static_cast<MatrixNumeric*>(a->args[0])->args)
            val *= scaling;
        delete a->scaling;
        return evaluate(a->args[0]);
    }

    //Symbolic//
    return expr;
}

Expr* Interpreter::read(Expr* expr){
    Q_ASSERT(expr->type == READ);
    Q_ASSERT(static_cast<Read*>(expr)->slot < stack.size());

    return evaluate(stack[static_cast<Read*>(expr)->slot]->clone());
}

}
