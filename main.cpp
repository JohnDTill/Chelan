#include "chelan.h"
using namespace Chelan;

// The root node has ownership and any nodes removed from the expression are freed

int main(int, char**){
    Expr* p0 = //Divide(RealVariable("x"), RealVariable("x"));
               //Divide(Pi(), Pi());
               new ScalarAddition({new Pi(), new Pi()});

    p0 = Expr::evaluateAndFree(p0); //This call simplifies to 2*pi

    Expr* r = new Read(p0);
    qDebug() << "Read: " << r->toMathBran() << "\n";

    p0 = Expr::evaluateAndFree(p0); //This sets string

    qDebug() << "Read: " << r->toMathBran() << "\n";

    qDebug() << "Output: " << p0->toMathBran() << "\n";

    p0->deleteChildren();
    delete p0;

    //Need to think about execution model, reading variables

    return 0;
}
