#ifndef DECLAREASSIGN_H
#define DECLAREASSIGN_H

#include "../stmt.h"

namespace Chelan {

class DeclareAssign : public Stmt{
private:
    Expr* rhs;

public:
    DeclareAssign(Expr* rhs);
    void execute(Runtime& runtime) override final;
};

}

#endif // DECLAREASSIGN_H
