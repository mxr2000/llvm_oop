//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_ACCESSEXPR_H
#define LLVM_OOP_ACCESSEXPR_H

#include "Expr.h"
#include <string>

class AccessExpr : public Expr {
private:
    Expr *lhs, *rhs;

public:
    AccessExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}

    Expr *Lhs() { return lhs; }

    Expr *Rhs() { return rhs; }

    GenValue * codegen(Context* ctx) override;
};

#endif //LLVM_OOP_ACCESSEXPR_H
