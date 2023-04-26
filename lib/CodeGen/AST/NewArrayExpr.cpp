//
// Created by Xinrun Miao on 4/25/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *NewArrayExpr::codegen(Context *ctx) {
    uint64_t elementSize;
    if (arrayType->ElementType()->isValueType()) {
        elementSize = ctx->getValueSize(dynamic_cast<ValueType *>(arrayType->ElementType()));
    } else {
        elementSize = ctx->getPointerSize();
    }
    auto count = countExpr->codegen(ctx);
    if (!count->Type()->isValueType()) {
        throw std::runtime_error("index is not int type");
    }
    auto size = ctx->Builder().CreateMul(ConstantInt::get(ctx->IntType, elementSize), count->Value());
    std::vector<Value *> callocArgs;
    callocArgs.push_back(ConstantInt::get(ctx->IntType, 1));
    callocArgs.push_back(size);
    auto calloc = ctx->Builder().CreateCall(ctx->CallocFunction, callocArgs, "calloced");
    return new GenValue(arrayType, calloc);
}


