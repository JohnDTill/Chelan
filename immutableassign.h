#ifndef IMMUTABLEASSIGN_H
#define IMMUTABLEASSIGN_H

#include "stmt.h"
#include <vector>

namespace Chelan {

class ImmutableAssign : public Stmt{
public:
    Expr* expr;

public:
    ImmutableAssign(Expr* expr);
};

}

#endif // IMMUTABLEASSIGN_H
