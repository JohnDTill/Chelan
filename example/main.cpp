#include "chelan.h"
using namespace Chelan;

// The root node has ownership and any nodes removed from the expression are freed

int main(int, char**){
    QString out;
    Runtime runtime(out);

    //ε = 10⁜^⏴-9⏵
    Expr* lhs0 = new Rational(10);
    Expr* rhs0 = new Rational(-9);
    Expr* eps = new ScalarPower(lhs0, rhs0);
    runtime.stack.push_back(eps);

    //a : (x) ↦ 2 + x
    Expr* body = new ScalarAddition({new Rational(2), new Read(1)});
    Expr* a = new Function(new Return(body));
    runtime.stack.push_back(a);

    Expr* p0 = //Divide(RealVariable("x"), RealVariable("x"));
               //Divide(Pi(), Pi());
               new ScalarAddition({new Pi(), new Pi()});

    //b : (x) ↦ (x + 3)(x - 2)
    Expr* lhs2 = new ScalarAddition({new Read(1), new Rational(3)});
    Expr* rhs2 = new ScalarAddition({new Read(1), new Rational(-2)});
    Expr* body2 = new ScalarMultiplication({lhs2, rhs2});
    Expr* b = new Function(new Return(body2));
    runtime.stack.push_back(b);

    //c : (x) ↦ ⁜⊞⏴2⏵⏴2⏵⏴2⏵⏴1⏵⏴3⏵⏴2⏵x + ⁜⊞⏴2⏵⏴1⏵⏴-3⏵⏴-4⏵
    Expr* A3 = new MatrixNumeric(2, 2, {2, 1, 3, 2});
    Expr* x3 = new Read(1);
    Expr* lhs3 = new MatrixMultiplication({A3, x3}, nullptr);
    Expr* rhs3 = new MatrixNumeric(2, 1, {-3, -4});
    Expr* body3 = new MatrixAddition({lhs3, rhs3});
    Expr* c = new Function(new Return(body3));
    runtime.stack.push_back(c);

    p0 = Expr::evaluateAndFree(p0, runtime); //This call simplifies to 2*pi
    runtime.stack.push_back(p0);

    Expr* r = new Read(1);
    qDebug() << "Read: " << r->toMathBran() << "\n";

    p0 = Expr::evaluateAndFree(p0, runtime); //This sets string

    qDebug() << "Read: " << r->toMathBran() << "\n";

    qDebug() << "Output: " << p0->toMathBran() << "\n";

    p0->deleteChildren();
    delete p0;

    //Need to think about execution model, reading variables

    return 0;
}
