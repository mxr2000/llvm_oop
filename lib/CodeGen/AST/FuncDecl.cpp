//
// Created by Xinrun Miao on 4/6/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"
#include <iostream>

GenValue * FuncDecl::codegen(Context *ctx) {
    if (ctx->GeneratedFunctions.count(this) != 0) {
        ctx->setCurFunction(ctx->GeneratedFunctions[this]);
        return nullptr;
    }
    if (this->header->Name() == "main" && this->header->ReturnType()->toString() != "Int") {
        std::cout << "return type of main must be int!";
    }
    llvm::Function* function{};
    if (ctx->IsInStaticMethod()) {
        function = ctx->getStaticMethod(header);
        if (function == nullptr) {
            throw std::runtime_error("static method is not found");
        }
    } else {
        function = ctx->createCurFunction(header);
    }
    ctx->setCurFunction(function);
    ctx->pushSymbolTable();
    auto f = ctx->CurFunction();
    if (!ctx->IsInStaticMethod()) {
        ctx->addValueToCurrentTable("self", new SelfGenValue(ctx->CurClass()->Type(), f->args().begin()));
    }
    auto entryBlock = ctx->createBasicBlock("entry");
    ctx->Builder().SetInsertPoint(entryBlock);

    for (int i = 0; i < header->Params().size(); i++) {
        int index = ctx->IsInStaticMethod() ? i : (i + 1);
        bool isPointerType = header->Params()[i]->Type()->isPointerType();
        auto alloc = ctx->Builder().CreateAlloca(ctx->IntPtrType);
        ctx->Builder().CreateStore(f->args().begin() + index, alloc);
        ctx->addValueToCurrentTable(header->Params()[i]->Name(),
                                    new GenValue(header->Params()[i]->Type(), alloc));
    }
    block->codegen(ctx);
    if (!isLastLineReturnStmt()) {
        if (header->ReturnType()->isVoid()) {
            ctx->Builder().CreateRetVoid();
        } else {
            //throw std::runtime_error("Last stmt is not return stmt");
        }
    }
    ctx->GeneratedFunctions.insert(std::make_pair(this, ctx->CurFunction()));
    ctx->popSymbolTable();
    return nullptr;
}