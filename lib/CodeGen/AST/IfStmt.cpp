//
// Created by Xinrun Miao on 4/1/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue * IfStmt::codegen(Context *ctx) {
    auto conditionValue = condition->codegen(ctx);

    auto thenBlock = ctx->createBasicBlock("then");
    auto elseBlock = ctx->createBasicBlock("else");
    auto mergeBlock = ctx->createBasicBlock("merge");

    ctx->Builder().CreateCondBr(conditionValue->Value(), thenBlock, elseBlock);

    ctx->Builder().SetInsertPoint(thenBlock);
    thenStmt->codegen(ctx);
    ctx->Builder().CreateBr(mergeBlock);

    ctx->Builder().SetInsertPoint(elseBlock);
    if (elseStmt != nullptr) {
        elseStmt->codegen(ctx);
    }
    ctx->Builder().CreateBr(mergeBlock);

    ctx->Builder().SetInsertPoint(mergeBlock);
    return nullptr;
}