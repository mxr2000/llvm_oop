//
// Created by Xinrun Miao on 4/5/23.
//
#include "llop/AST/AST.h"
#include "llop/CodeGen/GenValue.h"
#include "llop/CodeGen/Context.h"

GenValue *VariableDeclStmt::codegen(Context *ctx) {
    auto value = ctx->Builder().CreateAlloca(ctx->IntPtrType);
    ctx->addValueToCurrentTable(Name(), new GenValue(type, value));
    return nullptr;
}