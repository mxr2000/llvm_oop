//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_BINARYEXPR_H
#define LLVM_OOP_BINARYEXPR_H

#include "Expr.h"
#include "BinaryOp.h"

class BinaryExpr : public Expr {
private:
    Expr *lhs, *rhs;
    BinaryOp op;
public:
    BinaryExpr(Expr *lhs, Expr *rhs, BinaryOp op) : lhs(lhs), rhs(rhs), op(op) {}

    Expr *Rhs() { return rhs; }

    Expr *Lhs() { return lhs; }

    BinaryOp BinaryOperation() { return op; }

    GenValue *codegen(Context* ctx) override;
};

#endif //LLVM_OOP_BINARYEXPR_H
