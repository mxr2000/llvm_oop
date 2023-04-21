//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *NewObjectExpr::codegen(Context *ctx) {
    auto sizeOfClass = ctx->getStructSize(type->Name());
    std::vector<Value *> callocArgs;
    callocArgs.push_back(ConstantInt::get(ctx->IntType, 1));
    callocArgs.push_back(ConstantInt::get(ctx->IntType, sizeOfClass));
    auto calloc = ctx->Builder().CreateCall(ctx->CallocFunction, callocArgs, "calloced");

    auto structType = ctx->getStructType(type->Name());
    auto vtable = ctx->getVtable(type->Name());
    ctx->Builder().CreateStore(
            vtable,
            ctx->Builder().CreateStructGEP(structType, calloc, 0));

    std::vector<Value*> args;
    args.push_back(calloc);
    for (auto expr: arguments) {
        args.push_back(expr->codegen(ctx)->Value());
    }

    std::vector<Value *> indices;
    indices.push_back(ConstantInt::get(ctx->IntType, 0));
    indices.push_back(ConstantInt::get(ctx->IntType, 2)); // index for init function
    auto tableType = ctx->getVtableType(type->Name());
    Value *fp = ctx->Builder().CreateGEP(tableType, vtable, indices);
    Value *f = ctx->Builder().CreateLoad(ctx->IntPtrType, fp);

    ctx->Builder().CreateCall(ctx->headerToLlvmType(ctx->getMethodHeader(type, 2), true), f, args);
    return new GenValue(type, calloc);
}
