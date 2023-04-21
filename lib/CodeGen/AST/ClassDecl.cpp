//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *ClassDecl::codegen(Context* ctx) {
    ctx->setCurClass(this);
    int index = 2;
    for (auto f: methods) {
        f->codegen(ctx);
        ctx->insertIntoVTableInitializer(Name(), index, ctx->CurFunction());
        ++index;
    }
    ctx->buildVTable(this);
    ctx->clearCurClass();
    return nullptr;
}