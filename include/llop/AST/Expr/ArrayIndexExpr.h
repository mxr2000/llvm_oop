//
// Created by Xinrun Miao on 4/25/23.
//

#ifndef LLVM_OOP_ARRAYINDEXEXPR_H
#define LLVM_OOP_ARRAYINDEXEXPR_H

#include "Expr.h"

class ArrayIndexExpr: public Expr {
private:
    Expr* lhs, *rhs;
public:
    ArrayIndexExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}

    Expr *Rhs() { return rhs; }

    Expr *Lhs() { return lhs; }

    GenValue *codegen(Context* ctx) override;
};

#endif //LLVM_OOP_ARRAYINDEXEXPR_H
