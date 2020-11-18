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
        Expr* while_cond_nr = new Less(emeps);
        Stmt* while_body_nr = new Block({get_J, asgn_del, reasgn_x, reasgn_r, reasgn_e});
        Stmt* nr_while = new While(while_cond_nr, while_body_nr, 2);

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

        //x comes in as a 2x1 vector

        //fx = f(x)
        Stmt* asgn_fx2 = new DeclareAssign(new Call(new ReadLocal(3, "f"), {new ReadLocal(2, "x")}, true));

        //J ∈ ℝ⁜^⏴n×n⏵
        Stmt* asgn_J2 = new DeclareAssign(new MatrixNumeric(2,2,{0,0,0,0}));

        //i ∈ ℤ,  i ← 1
        Stmt* asgn_i2 = new DeclareAssign(new Rational(0));

            //x is a vector here

            //x⁜_⏴i⏵ ← x⁜_⏴i⏵ + δ
            Stmt* incr_xi2 = new AssignElement(5, new ScalarAddition({new ReadLocalElement(5, "x", new ReadLocal(1, "i")), new ReadLocal(4, QString("δ"))}), new ReadLocal(1, "i"));

            //x is a 2x1 vector, and correct on both iterations

            //J⁜_⏴1:n,i⏵ ← ⁜f⏴f(x) - fx⏵⏴δ⏵
            Expr* fx2 = new Call(new ReadLocal(6, "f"), {new ReadLocal(5, "x")}, true);
            //x is rational on call
            //This happens without reassignment of x
            //I think x is at offset 5- it is the first argument
            //c is called with the correct coefficients, but returns the wrong value
                //PROBABLY A MATRIX MULTIPLICATION PROBLEM
                //The matrix multiplication sees the both args correctly
            //The A matrix is correct
            //fx2 is [-3;-4] for the 2nd column because the increment fails, but the index incremented is correct
            Expr* diff2 = new MatrixAddition({fx2, new MatrixMultiplication({new ReadLocal(3, "fx")}, new Rational(-1))});
            Expr* fd2 = new MatrixMultiplication({diff2}, new ScalarPower(new ReadLocal(4, QString("δ")), new Rational(-1)));
            //fd2 is [0;0] for the 2nd column
            Stmt* asgn_Jcol2 = new AssignColumn(2, fd2, new ReadLocal(1, "i"));

            //x⁜_⏴i⏵ ← x⁜_⏴i⏵ - δ
            Stmt* decr_xi2 = new AssignElement(5, new ScalarAddition({new ReadLocalElement(5, "x", new ReadLocal(1, "i")), new ScalarMultiplication(new ReadLocal(4, QString("δ")), -1)}), new ReadLocal(1, "i"));

            //i ← i + 1
            Stmt* reasgn_i2 = new Assign(1, new ScalarAddition({new ReadLocal(1, "i"), new Rational(1)}));

        //i ≤ n
        Expr* imn2 = new ScalarAddition({new ReadLocal(1, "i"), new Rational(-1)});
        Expr* while_cond2 = new Disjunction({new Less(imn2), new Equality(imn2->clone())});
        Stmt* while_body2 = new Block({incr_xi2, asgn_Jcol2, decr_xi2, reasgn_i2});
        Stmt* jacob_while2 = new While(while_cond2, while_body2, 0);

        //return J
        Stmt* jacob_return2 = new Return(new ReadLocal(2, "J"), 6);

    //algorithm getJacobian(n ∈ ℕ, f : ℝ⁜^⏴n⏵→ ℝ⁜^⏴n⏵, x ∈ ℝ⁜^⏴n⏵, δ ∈ ℝ⁜^⏴+⏵)
    Expr* getJacobian2 = new Function(new Block({asgn_fx2, asgn_J2, asgn_i2, jacob_while2, jacob_return2}), "getJacobian");
    Stmt* gj2 = new DeclareAssign(getJacobian2);

        //r ∈ ℝ⁜^⏴n⏵,  r ← f(x)
        Stmt* asgn_r2 = new DeclareAssign(new Call(new ReadLocal(3, "f"), {new ReadLocal(2, "x")}, true));

        //e ∈ ℝ,   e ← r ⋅ r
        Stmt* asgn_e2 = new DeclareAssign(new MatrixMultiplication({new Transpose(new ReadLocal(1, "r")), new ReadLocal(1, "r")}, new Rational(1)));

            //J = getJacobian(n, f, x, 10⁜^⏴-4⏵)
            Stmt* get_J2 = new DeclareAssign(new Call(new ReadGlobal(5, "getJacobian2"), {new ReadLocal(5, "f"), new ReadLocal(5, "x"), new ScalarPower(new Rational(10), new Rational(-4))}, true));

            //δ = -J⁜^⏴-1⏵r
            Stmt* asgn_del2 = new DeclareAssign(new MatrixMultiplication({new Inverse(new ReadLocal(1, "J")), new ReadLocal(3, "r")}, new Rational(-1)));

            //x ← x + δ
            Stmt* reasgn_x2 = new Assign(6, new MatrixAddition({new ReadLocal(6, "x"), new ReadLocal(1, QString("δ"))}));

            //r ← f(x)
            Stmt* reasgn_r2 = new Assign(4, new Call(new ReadLocal(7, "f"), {new ReadLocal(6, "x")}, true));

            //e ← r ⋅ r
            Stmt* reasgn_e2 = new Assign(3, new MatrixMultiplication({new Transpose(new ReadLocal(4, "r")), new ReadLocal(4, "r")}, new Rational(1)));

        //e > ε
        Expr* emeps2 = new ScalarAddition({new ReadLocal(3, QString("ε")), new ScalarMultiplication(new AbsoluteValue(new ReadLocal(1, "e")), -1)});
        Expr* while_cond_nr2 = new Less(emeps2);
        Stmt* while_body_nr2 = new Block({get_J2, asgn_del2, reasgn_x2, reasgn_r2, reasgn_e2});
        Stmt* nr_while2 = new While(while_cond_nr2, while_body_nr2, 2);

        //return x
        Stmt* nr_return2 = new Return(new ReadLocal(4, "x"), 6);

    //algorithm NewtonRaphson(n ∈ ℕ, f : ℝ⁜^⏴n⏵→ ℝ⁜^⏴n⏵, x ∈ ℝ⁜^⏴n⏵, ε ∈ ℝ⁜^⏴+⏵)
    Expr* NewtonRaphson2 = new Function(new Block({asgn_r2, asgn_e2, nr_while2, nr_return2}), "NewtonRaphson");
    Stmt* nr2 = new DeclareAssign(NewtonRaphson2);

    //c : (x) ↦ ⁜⊞⏴2⏵⏴2⏵⏴2⏵⏴1⏵⏴3⏵⏴2⏵x + ⁜⊞⏴2⏵⏴1⏵⏴-3⏵⏴-4⏵
    Expr* A3 = new MatrixNumeric(2, 2, {2, 1, 3, 2});
    Expr* x3 = new ReadLocal(1, "x");
    Expr* lhs3 = new MatrixMultiplication({A3, x3}, new Rational(1));
    Expr* rhs3 = new MatrixNumeric(2, 1, {-3, -4});
    Expr* body3 = new MatrixAddition({lhs3, rhs3});
    Expr* c = new Function(new Return(body3, 1), "c");
    Stmt* asgn_c = new DeclareAssign(c);

    //print(NewtonRaphson(2, c, ⁜⊞⏴2⏵⏴1⏵⏴0⏵⏴0⏵, ε))
    Expr* call_c = new Call(new ReadGlobal(6, "NewtonRaphson2"), {new Rational(1), new ReadGlobal(7, "c"), new MatrixNumeric(2, 1, {0, 0}), new ReadGlobal(2, QString("ε"))}, true);
    Stmt* print_c = new Print(call_c);

    Stmt* main2 = new Block({gj, nr, asgn, asgn_a, print_a, asgn_b, print_b, gj2, nr2, asgn_c, print_c});

    //Run
    QString out;
    Runtime runtime(out);

    try{
        main2->execute(runtime);
        qDebug() << out;
    }catch(int i){
        if(i==1)
            qDebug() << out;
        else
            throw(i);
    }

    return 0;
}
