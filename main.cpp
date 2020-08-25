#include "chelan.h"
using namespace AST;

// The root node has ownership and any nodes removed from the expression are freed

int main(int, char**){
    Node* p0 = Divide(RealVariable('x'), RealVariable('x'));
               //Divide(Pi(), Pi());

    qDebug() << "Output: " << p0->toString() << "\n";

    p0->deleteChildren();
    delete p0;

    return 0;
}
