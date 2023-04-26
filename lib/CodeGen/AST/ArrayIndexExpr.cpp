//
// Created by Xinrun Miao on 4/25/23.
//
#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *ArrayIndexExpr::codegen(Context *ctx) {
    ctx->incrementAccessLevel();
    auto l = lhs->codegen(ctx);
    if (!l->Type()->isArrayType()) {
        throw std::runtime_error("Lhs is not an array type");
    }
    auto indexVal = rhs->codegen(ctx);
    if (!indexVal->Type()->isValueType()) {
        throw std::runtime_error("Rhs is not a value type");
    }
    auto arrayType = dynamic_cast<::ArrayType *>(l->Type());
    auto elementType = arrayType->ElementType();
    Value *address;
    std::vector<Value *> indices;
    indices.push_back(ConstantInt::get(ctx->IntType, 0));
    //indices.push_back(ConstantInt::get(ctx->IntType, 0));
    indices.push_back(indexVal->Value());
    if (elementType->isValueType()) {
        address = ctx->Builder().CreateGEP(
                llvm::ArrayType::get(ctx->BasicTypes[dynamic_cast<ValueType *>(elementType)->BasicType()], 0),
                l->Value(),
                indices
        );
    } else {
        address = ctx->Builder().CreateGEP(
                llvm::ArrayType::get(ctx->IntPtrType, 0),
                l->Value(),
                indices
        );
    }
    ctx->decrementLevelAccess(); // decrement level access before first accessing rhs
    bool loadPointer = ctx->LeftValueFlag() && ctx->TopLevelAccess();
    auto result = new GenValue(elementType, address);

    return loadPointer ? result : ctx->getLoadedValue(result);
}