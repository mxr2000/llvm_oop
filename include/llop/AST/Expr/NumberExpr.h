//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_NUMBEREXPR_H
#define LLVM_OOP_NUMBEREXPR_H
#include "Expr.h"

class NumberExpr : public Expr {
private:
    int val;
public:
    explicit NumberExpr(int val) : val(val) {}
    int Val() const { return val; }

    GenValue * codegen(Context* ctx) override;
};
#endif //LLVM_OOP_NUMBEREXPR_H
