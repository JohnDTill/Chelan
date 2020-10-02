#include "matrixnumeric.h"

#include "chelan.h"

namespace Chelan{

MatrixNumeric::MatrixNumeric(vInt rows, vInt cols, const std::vector<mpq_class>& args)
    : Expr(MATRIX_NUMERIC), rows(rows), cols(cols), args(args){}

Expr* MatrixNumeric::clone() const{
    return new MatrixNumeric(rows, cols, args);
}

Expr* MatrixNumeric::evaluate(){
    if(rows == 1 && cols == 1) return new Rational(args[0]);

    return nullptr;
}

void MatrixNumeric::writeMathBran(QTextStream& out, Precedence) const{
    out << "⁜⊞⏴" << rows << "⏵⏴" << cols;
    for(mpq_class n : args)
        out << "⏵⏴" << QString::fromStdString(n.get_str());
    out << "⏵";
}

const mpq_class& MatrixNumeric::at(std::vector<mpq_class>::size_type row,
                                   std::vector<mpq_class>::size_type col) const{
    Q_ASSERT(col < cols);
    Q_ASSERT(row < rows);

    return args[col + cols*row];
}

}
