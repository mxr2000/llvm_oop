//
// Created by Xinrun Miao on 4/2/23.
//
#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *NotExpr::codegen(Context *ctx) {
    auto val = expr->codegen(ctx);
    auto result = ctx->Builder().CreateICmpEQ(val->Value(), ctx->ZeroInt);
    return new GenValue(val->Type(), result);
}