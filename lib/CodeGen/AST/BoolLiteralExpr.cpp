//
// Created by Xinrun Miao on 4/25/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue * BoolLiteralExpr::codegen(Context *ctx) {
    auto val = ConstantInt::get(ctx->BasicTypes[BasicType::Bool], value ? 1 : 0);
    return new GenValue(ValueType::BoolType, val);
}