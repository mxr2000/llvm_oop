//
// Created by Xinrun Miao on 4/5/23.
//

#ifndef LLVM_OOP_SELFEXPR_H
#define LLVM_OOP_SELFEXPR_H

#include "Expr.h"
#include "../../CodeGen/GenValue.h"

class SelfExpr : public Expr {
public:
    GenValue *codegen(Context* ctx) override;
};


#endif //LLVM_OOP_SELFEXPR_H
