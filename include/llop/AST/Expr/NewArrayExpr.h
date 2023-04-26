//
// Created by Xinrun Miao on 4/25/23.
//

#ifndef LLVM_OOP_NEWARRAYEXPR_H
#define LLVM_OOP_NEWARRAYEXPR_H

#include "Expr.h"
#include "../Type/ArrayType.h"

class NewArrayExpr : public Expr {
private:
    ArrayType *arrayType;
    Expr *countExpr;
public:
    NewArrayExpr(ArrayType *arrayType, Expr *countExpr) : arrayType(arrayType), countExpr(countExpr) {}

    ArrayType *ArrayType() { return arrayType; }
    Expr *CountExpr() {return countExpr;}
    GenValue * codegen(Context *ctx) override;
};

#endif //LLVM_OOP_NEWARRAYEXPR_H
