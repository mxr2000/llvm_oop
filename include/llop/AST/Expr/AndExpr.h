//
// Created by Xinrun Miao on 4/2/23.
//

#ifndef LLVM_OOP_ANDEXPR_H
#define LLVM_OOP_ANDEXPR_H

#include "Expr.h"

class AndExpr : public Expr {
private:
    Expr *lhs, *rhs;
public:
    AndExpr(Expr *lhs, Expr* rhs): lhs(lhs), rhs(rhs) {}

    GenValue * codegen(Context* ctx) override;
};

#endif //LLVM_OOP_ANDEXPR_H
