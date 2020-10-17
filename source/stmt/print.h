#include "../stmt.h"

#include "../expr.h"

namespace Chelan {

class Print : public Stmt{
private:
    Expr* e;

public:
    Print(Expr* e);
    virtual bool execute(Runtime& runtime) override;
};

}
