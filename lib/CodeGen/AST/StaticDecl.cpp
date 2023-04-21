//
// Created by Xinrun Miao on 4/5/23.
//
#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue * StaticDecl::codegen(Context *ctx) {
    ctx->setCurStatic(this);
    for (auto f: methods) {
        f->codegen(ctx);
    }
    ctx->clearCurStatic();
    return nullptr;
}

void StaticDecl::createFunctions(Context *ctx) {
    for (auto f: methods) {
        ctx->createStaticFunction(Name(), f->Header());
    }
}