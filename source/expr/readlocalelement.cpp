#include "readlocalelement.h"

#include <chelan.h>

namespace Chelan {

ReadLocalElement::ReadLocalElement(std::vector<Expr*>::size_type offset, const QString& id, Expr* index)
    : Expr(READ), offset(offset), id(id), index(index) {}

Expr* ReadLocalElement::clone() const{
    return new ReadLocalElement(offset, id, index->clone());
}

Expr* ReadLocalElement::evaluate(Runtime& runtime){
    Expr* read = Expr::evaluateAndFree(runtime.stack[runtime.stack.size()-offset]->clone(), runtime);
    if(read->type != MATRIX_NUMERIC){
        runtime.out << "ERROR: tried to read element of non-matrix expr: " << read->toMathBran();
        Expr::deleteRecursive(read);
        throw 1;
    }

    MatrixNumeric* m = static_cast<MatrixNumeric*>(read);
    if(m->rows > 1 && m->cols > 1){
        runtime.out << "ERROR: tried to read element of 2D matrix: " << read->toMathBran();
        delete m;
        throw 1;
    }

    Expr* index_eval = Expr::evaluateAndFree( index->clone(), runtime );

    if(index_eval->type != RATIONAL){
        runtime.out << "ERROR: read subscript did not evaluate: " << index_eval->toMathBran();
        Expr::deleteRecursive(index_eval);
        delete m;
        throw 1;
    }

    mpq_class r = static_cast<Rational*>(index_eval)->value;
    delete index_eval;
    if(r.get_den() != 1){
        runtime.out << "ERROR: read subscript with non-integer index: " << r.get_str().c_str();
        delete m;
        throw 1;
    }else if(r < 0){
        runtime.out << "ERROR: read subscript with negative integer index: " << r.get_str().c_str();
        delete m;
        throw 1;
    }
    unsigned long long index = r.get_num().get_ui();

    std::vector<mpq_class>& args = m->args;
    if(index >= args.size()){
        runtime.out << "ERROR: tried to access element " << index
                    << " of a vector with " << args.size() << " entries";
        delete m;
        throw 1;
    }

    Expr* e = new Rational(args[index]);
    delete m;

    return e;
}

void ReadLocalElement::writeMathBran(QTextStream& out, Precedence) const{
    out << id;
}

}
