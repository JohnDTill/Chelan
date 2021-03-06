#ifndef STMT_H
#define STMT_H

#include "runtime.h"

namespace Chelan {

class Stmt{
public:
    virtual void execute(Runtime& runtime) = 0;
};

}

#endif // STMT_H
