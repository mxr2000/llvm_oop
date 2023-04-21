//
// Created by Xinrun Miao on 4/2/23.
//

#ifndef LLVM_OOP_NEGEXPR_H
#define LLVM_OOP_NEGEXPR_H

#include "Expr.h"

class NegExpr : public Expr {
private:
    Expr *expr;
public:
    explicit NegExpr(Expr *expr) : expr(expr) {}

    Expr *getExpr() { return expr; }

    GenValue *codegen(Context* ctx) override;
};

#endif //LLVM_OOP_NEGEXPR_H
