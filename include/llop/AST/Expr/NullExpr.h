//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_NULLEXPR_H
#define LLVM_OOP_NULLEXPR_H

#include "Expr.h"

class NullExpr : public Expr {

public:
    GenValue *codegen(Context* ctx) override { return nullptr; }
};

#endif //LLVM_OOP_NULLEXPR_H
