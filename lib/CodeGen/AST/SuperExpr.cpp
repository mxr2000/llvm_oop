//
// Created by Xinrun Miao on 4/17/23.
//
#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue * SuperExpr::codegen(Context *ctx) {
    return ctx->Super();
}