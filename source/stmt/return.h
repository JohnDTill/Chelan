#ifndef RETURN_H
#define RETURN_H

#include "../stmt.h"

#include "../expr.h"

namespace Chelan {

class Return : public Stmt{
private:
    Expr* e;
public:
    Return(Expr* e);
    virtual bool execute(Runtime& runtime) override final;
};

}

#endif // RETURN_H
