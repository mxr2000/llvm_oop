//
// Created by Xinrun Miao on 4/2/23.
//

#ifndef LLVM_OOP_OREXPR_H
#define LLVM_OOP_OREXPR_H

#include "Expr.h"

class OrExpr : public Expr {
private:
    Expr *lhs, *rhs;
public:
    OrExpr(Expr *lhs, Expr* rhs): lhs(lhs), rhs(rhs) {}

    GenValue * codegen(Context* ctx) override;
};

#endif //LLVM_OOP_OREXPR_H
