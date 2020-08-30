#ifndef PRINT_H
#define PRINT_H

#include "stmt.h"

namespace Chelan {

class Print : public Stmt{
public:
    Expr* expr;

public:
    Print(Expr* expr);
};

}

#endif // PRINT_H
