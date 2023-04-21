//
// Created by Xinrun Miao on 4/1/23.
//


#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *ReturnStmt::codegen(Context *ctx) {
    if (expr == nullptr) {
        ctx->Builder().CreateRetVoid();
    } else {
        auto value = expr->codegen(ctx);
        ctx->Builder().CreateRet(value->Value());
    }
    return nullptr;
}
