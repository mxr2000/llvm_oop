//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *Program::codegen(Context *ctx) {
    for (auto interfaceDecl: interfaceDecls) {
        interfaceDecl.second->codegen(ctx);
    }
    for (auto staticDecl: staticDecls) {
        staticDecl.second->createFunctions(ctx);
    }
    for (auto staticDecl: staticDecls) {
        staticDecl.second->codegen(ctx);
    }
    int id = 0;
    for (auto classDecl: classDecls) {
        ctx->setClassIndex(classDecl.first, id);
        classDecl.second->codegen(ctx);
        ++id;
    }
    return nullptr;
}