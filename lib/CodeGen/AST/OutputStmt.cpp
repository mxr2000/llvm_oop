//
// Created by Xinrun Miao on 4/19/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *OutputStmt::codegen(Context *ctx) {
    auto val = expr->codegen(ctx);
    if (val->Type()->toString() != "Int") {
        throw std::runtime_error("Can only output integer");
    }
    std::vector<Value *> args;
    args.push_back(val->Value());
    ctx->Builder().CreateCall(ctx->OutputFunction, args);
    return nullptr;
}
