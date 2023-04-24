//
// Created by Xinrun Miao on 4/1/23.
//


#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *WhileStmt::codegen(Context *ctx) {
    auto headerBlock = ctx->createBasicBlock("header");
    auto bodyBlock = ctx->createBasicBlock("body");
    auto exitBlock = ctx->createBasicBlock("exit");

    ctx->Builder().CreateBr(headerBlock);

    ctx->Builder().SetInsertPoint(headerBlock);
    auto conditionValue = condition->codegen(ctx);
    ctx->Builder().CreateCondBr(conditionValue->Value(), bodyBlock, exitBlock);

    ctx->Builder().SetInsertPoint(bodyBlock);
    body->codegen(ctx);
    ctx->Builder().CreateBr(headerBlock);

    ctx->Builder().SetInsertPoint(exitBlock);
    return nullptr;
}
