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
    for (auto classDecl: classDecls) {
        classDecl.second->codegen(ctx);
    }
    return nullptr;
}