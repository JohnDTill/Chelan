#include "chelan.h"
using namespace Chelan;

int main(int, char**){
        //fx = f(x)
        Stmt* asgn_fx = new DeclareAssign(new Call(new ReadLocal(3, "f"), {new ReadLocal(2, "x")}, true));

        //J ∈ ℝ⁜^⏴n×n⏵
        Stmt* asgn_J = new DeclareAssign(new Rational(0));
        //DO THIS- this is bad. You haven't weighed initialization, particularly of matrices.

        //i ∈ ℤ,  i ← 1
        Stmt* asgn_i = new DeclareAssign(new Rational(1));

            //x⁜_⏴i⏵ ← x⁜_⏴i⏵ + δ
            Stmt* incr_xi = new Assign(5, new ScalarAddition({new ReadLocal(5, "x"), new ReadLocal(4, QString("δ"))}));

            //J⁜_⏴1:n,i⏵ ← ⁜f⏴f(x) - fx⏵⏴δ⏵
            Expr* fx = new Call(new ReadLocal(6, "f"), {new ReadLocal(5, "x")}, true);
            Expr* diff = new ScalarAddition({fx, new ScalarMultiplication(new ReadLocal(3, "fx"),-1)});
            Expr* fd = new ScalarMultiplication({diff, new ScalarPower(new ReadLocal(4, QString("δ")), new Rational(-1))});
            Stmt* asgn_Jcol = new Assign(2, fd);

            //x⁜_⏴i⏵ ← x⁜_⏴i⏵ - δ
            Stmt* decr_xi = new Assign(5, new ScalarAddition({new ReadLocal(5, "x"), new ScalarMultiplication(new ReadLocal(4, QString("δ")), -1)}));

            //i ← i + 1
            Stmt* reasgn_i = new Assign(1, new ScalarAddition({new ReadLocal(1, "i"), new Rational(1)}));

        //i ≤ n
        Expr* imn = new ScalarAddition({new ReadLocal(1, "i"), new Rational(-1)});
        Expr* while_cond = new Disjunction({new Less(imn), new Equality(imn->clone())});
        Stmt* while_body = new Block({incr_xi, asgn_Jcol, decr_xi, reasgn_i});
        Stmt* jacob_while = new While(while_cond, while_body, 0);

        //return J
        Stmt* jacob_return = new Return(new ReadLocal(2, "J"), 6);

    //algorithm getJacobian(n ∈ ℕ, f : ℝ⁜^⏴n⏵→ ℝ⁜^⏴n⏵, x ∈ ℝ⁜^⏴n⏵, δ ∈ ℝ⁜^⏴+⏵)
    Expr* getJacobian = new Function(new Block({asgn_fx, asgn_J, asgn_i, jacob_while, jacob_return}), "getJacobian");
    Stmt* gj = new DeclareAssign(getJacobian);

        //r ∈ ℝ⁜^⏴n⏵,  r ← f(x)
        Stmt* asgn_r = new DeclareAssign(new Call(new ReadLocal(3, "f"), {new ReadLocal(2, "x")}, true));

        //e ∈ ℝ,   e ← r ⋅ r
        Stmt* asgn_e = new DeclareAssign(new ScalarMultiplication({new ReadLocal(1, "r"), new ReadLocal(1, "r")}));

            //J = getJacobian(n, f, x, 10⁜^⏴-4⏵)
            Stmt* get_J = new DeclareAssign(new Call(new ReadGlobal(0, "getJacobian"), {new ReadLocal(5, "f"), new ReadLocal(5, "x"), new ScalarPower(new Rational(10), new Rational(-4))}, true));

            //δ = -J⁜^⏴-1⏵r
            Stmt* asgn_del = new DeclareAssign(new ScalarMultiplication({new Rational(-1), new ReadLocal(3, "r"), new ScalarPower(new ReadLocal(1, "J"), new Rational(-1))}));

            //x ← x + δ
            Stmt* reasgn_x = new Assign(6, new ScalarAddition({new ReadLocal(6, "x"), new ReadLocal(1, QString("δ"))}));

            //r ← f(x)
            Stmt* reasgn_r = new Assign(4, new Call(new ReadLocal(7, "f"), {new ReadLocal(6, "x")}, true));

            //e ← r ⋅ r
            Stmt* reasgn_e = new Assign(3, new ScalarMultiplication({new ReadLocal(4, "r"), new ReadLocal(4, "r")}));

        //e > ε
        Expr* emeps = new ScalarAddition({new ReadLocal(3, QString("ε")), new ScalarMultiplication(new AbsoluteValue(new ReadLocal(1, "e")), -1)});
        Expr* while_cond2 = new Less(emeps);
        Stmt* while_body2 = new Block({get_J, asgn_del, reasgn_x, reasgn_r, reasgn_e});
        Stmt* nr_while = new While(while_cond2, while_body2, 2);

        //return x
        Stmt* nr_return = new Return(new ReadLocal(4, "x"), 6);

    //algorithm NewtonRaphson(n ∈ ℕ, f : ℝ⁜^⏴n⏵→ ℝ⁜^⏴n⏵, x ∈ ℝ⁜^⏴n⏵, ε ∈ ℝ⁜^⏴+⏵)
    Expr* NewtonRaphson = new Function(new Block({asgn_r, asgn_e, nr_while, nr_return}), "NewtonRaphson");
    Stmt* nr = new DeclareAssign(NewtonRaphson);

    //ε = 10⁜^⏴-9⏵
    Expr* lhs0 = new Rational(10);
    Expr* rhs0 = new Rational(-9);
    Expr* eps = new ScalarPower(lhs0, rhs0);
    Stmt* asgn = new DeclareAssign(eps);

    //a : (x) ↦ 2 + x
    Expr* body = new ScalarAddition({new Rational(2), new ReadLocal(1, "x")});
    Expr* a = new Function(new Return(body, 1), "a");
    Stmt* asgn_a = new DeclareAssign(a);

    //print(NewtonRaphson(1, a, 0, ε))
    Expr* call_a = new Call(new ReadGlobal(1, "NewtonRaphson"), {new Rational(1), new ReadGlobal(3, "a"), new Rational(0), new ReadGlobal(2, QString("ε"))}, true);
    Stmt* print_a = new Print(call_a);

    //b : (x) ↦ (x - 3)(x - 2) //The error reaches a point where exponentiation doesn't work.
    Expr* lhs2 = new ScalarAddition({new ReadLocal(1, "x"), new Rational(-3)});
    Expr* rhs2 = new ScalarAddition({new ReadLocal(1, "x"), new Rational(-2)});
    Expr* body2 = new ScalarMultiplication({lhs2, rhs2});
    Expr* b = new Function(new Return(body2, 1), "b");
    Stmt* asgn_b = new DeclareAssign(b);

    //print(NewtonRaphson(1, b, 0, ε))
    Expr* call_b = new Call(new ReadGlobal(1, "NewtonRaphson"), {new Rational(1), new ReadGlobal(4, "b"), new Rational(0), new ReadGlobal(2, QString("ε"))}, true);
    Stmt* print_b = new Print(call_b);

    Stmt* main = new Block({gj, nr, asgn, asgn_a, print_a, asgn_b, print_b});

    //c : (x) ↦ ⁜⊞⏴2⏵⏴2⏵⏴2⏵⏴1⏵⏴3⏵⏴2⏵x + ⁜⊞⏴2⏵⏴1⏵⏴-3⏵⏴-4⏵
    //Expr* A3 = new MatrixNumeric(2, 2, {2, 1, 3, 2});
    //Expr* x3 = new Read(1, "x");
    //Expr* lhs3 = new MatrixMultiplication({A3, x3}, nullptr);
    //Expr* rhs3 = new MatrixNumeric(2, 1, {-3, -4});
    //Expr* body3 = new MatrixAddition({lhs3, rhs3});
    //Expr* c = new Function(new Return(body3, 1), "c");
    //Stmt* asgn_c = new DeclareAssign(c);

    //print(NewtonRaphson(2, c, ⁜⊞⏴2⏵⏴1⏵⏴0⏵⏴0⏵, ε))
    //Expr* call_c = new Call(new Read(5, "NewtonRaphson"), {new Rational(1), new Read(1, "c"), new MatrixNumeric(2, 1, {0, 0}), new Read(4, "ε")}, true);
    //Stmt* print_c = new Print(call_c);

    //Stmt* main = new Block({gj, nr, asgn, asgn_a, print_a, asgn_b, print_b, asgn_c, print_c});

    //Run
    QString out;
    Runtime runtime(out);

    try{
        main->execute(runtime);
        qDebug() << out;
    }catch(int i){
        if(i==1)
            qDebug() << out;
        else
            throw(i);
    }

    return 0;
}
