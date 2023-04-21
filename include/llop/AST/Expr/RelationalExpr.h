//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_RELATIONALEXPR_H
#define LLVM_OOP_RELATIONALEXPR_H

#include "Expr.h"
#include "RelationalOp.h"


class RelationalExpr : public Expr {
private:
    Expr *lhs, *rhs;
    RelationalOp op;
public:
    RelationalExpr(Expr *lhs, Expr *rhs, RelationalOp op) : lhs(lhs), rhs(rhs), op(op) {}

    Expr *Rhs() { return rhs; }

    Expr *Lhs() { return lhs; }

    RelationalOp RelationalOp() { return op; }

    GenValue *codegen(Context* ctx) override;
};

#endif //LLVM_OOP_RELATIONALEXPR_H
