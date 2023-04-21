//
// Created by Xinrun Miao on 4/2/23.
//
#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *NegExpr::codegen(Context *ctx) {
    auto val = expr->codegen(ctx);
    if (val == nullptr || val->Type()->toString() != "Int") {
        throw std::runtime_error("expr is null or type is not int");
    }
    auto negVal = ctx->Builder().CreateNeg(val->Value());
    return new GenValue(val->Type(), negVal);
}