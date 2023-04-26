//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *NumberExpr::codegen(Context *ctx) {
    auto value = ConstantInt::get(ctx->IntType, val);
    return new GenValue(ValueType::IntType, value);
}