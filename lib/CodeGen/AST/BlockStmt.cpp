//
// Created by Xinrun Miao on 4/2/23.
//


#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *BlockStmt::codegen(Context* ctx) {
    ctx->pushSymbolTable();
    for (auto stmt : stmts) {
        stmt->codegen(ctx);
    }
    ctx->popSymbolTable();
    return nullptr;
}