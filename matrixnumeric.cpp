#include "matrixnumeric.h"

#include "chelan.h"

namespace Chelan{

MatrixNumeric::MatrixNumeric(int rows, int cols, const std::vector<mpq_class>& args)
    : Expr(MATRIX_NUMERIC),
      rows(rows),
      cols(cols),
      args(args){}

Expr* MatrixNumeric::clone() const{
    return new MatrixNumeric(rows, cols, args);
}

Expr* MatrixNumeric::evaluate(){
    return nullptr;
}

QString MatrixNumeric::toMathBran(Expr::Precedence) const{
    QString str = "⁜⊞⏴" + QString::number(rows) + "⏵⏴" + QString::number(cols) + "⏵";
    for(mpq_class n : args) str += "⏴" + QString::fromStdString(n.get_str()) + "⏵";
    return str;
}

void MatrixNumeric::visitChildren(Interpreter*){
    //DO NOTHING
}

const mpq_class& MatrixNumeric::at(std::vector<mpq_class>::size_type row,
                                   std::vector<mpq_class>::size_type col) const{
    Q_ASSERT(col < cols);
    Q_ASSERT(row < rows);

    return args[col + cols*row];
}

}
