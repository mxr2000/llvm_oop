//
// Created by Xinrun Miao on 4/5/23.
//
#include "llop/AST/AST.h"
#include "llop/CodeGen/GenValue.h"
#include "llop/CodeGen/Context.h"

GenValue *VariableDeclStmt::codegen(Context *ctx) {
    Value* value;
    if (type->isPointerType()) {
        value = ctx->Builder().CreateAlloca(ctx->IntPtrType);

    } else {
        auto basicType = dynamic_cast<ValueType*>(type);
        value = ctx->Builder().CreateAlloca(ctx->BasicTypes[basicType->BasicType()]);
    }
    ctx->addValueToCurrentTable(Name(), new GenValue(type, value));
    return nullptr;
}