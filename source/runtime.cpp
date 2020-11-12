#include "runtime.h"

#include "expr.h"
#include <QTextCodec>

namespace Chelan{

QString Runtime::toMathBran() const{
    QString str;
    QTextStream out(&str);
    out.setCodec(QTextCodec::codecForMib(106)); //UTF8
    unsigned i = 0;
    for(const Expr* e : stack){
        out << QString::number(i++) << ": ";
        e->writeMathBran(out);
        out << '\n';
    }
    return str;
}

}
