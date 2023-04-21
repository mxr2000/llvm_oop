//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *AccessExpr::codegen(Context* ctx) {
    ctx->incrementAccessLevel();
    auto l = lhs->codegen(ctx);
    if (!l->Type()->isPointerType()) {
        throw std::runtime_error("Lhs is not a reference type");
    }
    ctx->decrementLevelAccess(); // decrement level access before first accessing rhs

    ctx->setReceiver(l); // set receiver before accessing rhs
    auto result = rhs->codegen(ctx);
    ctx->clearReceiver(); // clear receiver after accessing rhs
    return result;
}
