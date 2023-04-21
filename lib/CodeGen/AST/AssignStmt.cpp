//
// Created by Xinrun Miao on 4/1/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *AssignStmt::codegen(Context* ctx) {
    auto r = rhs->codegen(ctx);

    ctx->setLeftValueFlag();

    auto l = lhs->codegen(ctx);

    ctx->clearLeftValueFlag();
    ctx->Builder().CreateStore(r->Value(), l->Value());
    return nullptr;
}
