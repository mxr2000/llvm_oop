//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *TypeCoercionExpr::codegen(Context *ctx) {
    auto value = expr->codegen(ctx);
    if (value->Type()->isValueType()) {
        //ctx->Builder().CreateTrunc()
        //ctx->Builder().CreateSExt()
    } else {

    }
    return new GenValue(type, value->Value());
}