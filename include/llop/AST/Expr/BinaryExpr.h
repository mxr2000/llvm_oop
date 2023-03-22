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
};

#endif //LLVM_OOP_BINARYEXPR_H
