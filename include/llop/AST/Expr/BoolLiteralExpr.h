//
// Created by Xinrun Miao on 4/25/23.
//

#ifndef LLVM_OOP_BOOLLITERALEXPR_H
#define LLVM_OOP_BOOLLITERALEXPR_H

#include "Expr.h"

class BoolLiteralExpr: public Expr {
private:
    bool value;
public:
    BoolLiteralExpr(bool value): value(value) {}

    GenValue * codegen(Context *ctx) override;
};

#endif //LLVM_OOP_BOOLLITERALEXPR_H
