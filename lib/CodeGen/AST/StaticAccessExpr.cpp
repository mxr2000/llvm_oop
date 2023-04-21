//
// Created by Xinrun Miao on 4/17/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue * StaticAccessExpr::codegen(Context *ctx) {
    ctx->setStaticAccess(type);
    return expr->codegen(ctx);
}
