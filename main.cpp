#include "chelan.h"
using namespace Chelan;

// The root node has ownership and any nodes removed from the expression are freed

int main(int, char**){
    Expr* p0 = //Divide(RealVariable("x"), RealVariable("x"));
               //Divide(Pi(), Pi());
               Add(Pi(), Pi());

    qDebug() << "Output: " << p0->toMathBran() << "\n";

    p0->deleteChildren();
    delete p0;

    return 0;
}
