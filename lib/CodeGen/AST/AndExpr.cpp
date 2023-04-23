//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"
#include <iostream>

GenValue *AndExpr::codegen(Context* ctx) {
    auto leftBlock = ctx->createBasicBlock("and_left");
    auto rightBlock = ctx->createBasicBlock("and_right");
    auto mergeBlock = ctx->createBasicBlock("and_merge");

    ctx->Builder().CreateBr(leftBlock);

    ctx->Builder().SetInsertPoint(leftBlock);
    auto l = lhs->codegen(ctx);
    ctx->Builder().CreateCondBr(l->Value(), rightBlock, mergeBlock);

    ctx->Builder().SetInsertPoint(rightBlock);
    auto r = rhs->codegen(ctx);
    ctx->Builder().CreateBr(mergeBlock);

    ctx->Builder().SetInsertPoint(mergeBlock);
    auto phi = ctx->Builder().CreatePHI(ctx->BooleanType, 2);

    phi->addIncoming(l->Value(), leftBlock);
    phi->addIncoming(r->Value(), rightBlock);

    return new GenValue(new ValueType("Int"), phi);
}