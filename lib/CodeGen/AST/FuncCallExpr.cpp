//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *FuncCallExpr::generateClassMethodCall(Context *ctx, std::vector<GenValue *> &genArgs) {
    GenValue *receiver = ctx->Receiver();
    if (receiver == nullptr) {
        receiver = ctx->Self();
    }
    auto pair = ctx->findCalledClassMethod(receiver->Type(), Name(), genArgs);
    if (pair.first != -1) {
        std::vector<Value *> args;
        args.push_back(receiver->Value());
        for (auto itr: genArgs) {
            args.push_back(itr->Value());
        }
        auto className = receiver->Type()->toString();
        auto tableType = ctx->getVtableType(className);

        Value *table = ctx->Builder().CreateLoad(PointerType::get(tableType, 0),
                                                 ctx->Builder().CreateStructGEP(ctx->getStructType(className), receiver->Value(), 0));
        // load virtual table of parent class
        if (receiver->isSuper()) {
            std::vector<Value *> indices;
            indices.push_back(ConstantInt::get(ctx->IntType, 0));
            indices.push_back(ConstantInt::get(ctx->IntType, 1));
            auto tp = ctx->Builder().CreateGEP(tableType, table, indices);
            table = ctx->Builder().CreateLoad(PointerType::get(tableType, 0), tp);
        }

        std::vector<Value *> indices;
        indices.push_back(ConstantInt::get(ctx->IntType, 0));
        indices.push_back(ConstantInt::get(ctx->IntType, pair.first + 2));

        Value *fp = ctx->Builder().CreateGEP(tableType, table, indices);
        Value *f = ctx->Builder().CreateLoad(ctx->IntPtrType, fp);

        auto result = ctx->Builder().CreateCall(ctx->headerToLlvmType(pair.second, true), f, args);
        return new GenValue(pair.second->ReturnType(), result);
    }
    return nullptr;
}

GenValue *FuncCallExpr::generateStaticMethodCall(Context *ctx, std::vector<GenValue *> &genArgs) {
    auto f = ctx->findCalledStaticFunction(Name(), genArgs);
    if (f.first == nullptr) {
        return nullptr;
    }
    std::vector<Value *> args;
    args.reserve(genArgs.size());
    for (auto itr: genArgs) {
        args.push_back(itr->Value());
    }
    auto result = ctx->Builder().CreateCall(ctx->headerToLlvmType(f.second, false), f.first, args);
    return new GenValue(f.second->ReturnType(), result);
}

GenValue *FuncCallExpr::codegen(Context *ctx) {
    std::vector<GenValue *> genArgs;
    genArgs.reserve(arguments.size());

    // clear the receiver to not mess up with arguments
    auto receiver = ctx->Receiver();
    ctx->clearReceiver();
    for (auto expr: arguments) {
        genArgs.push_back(expr->codegen(ctx));
    }
    ctx->setReceiver(receiver);
    GenValue *result{};

    // If static access class is not set, try to generate class method call
    if (!ctx->StaticAccessClass() && !(receiver == nullptr && ctx->IsInStaticMethod())) {
        result = generateClassMethodCall(ctx, genArgs);
    }

    if (result == nullptr) {
        result = generateStaticMethodCall(ctx, genArgs);
    }

    if (result == nullptr) {
        throw std::runtime_error("method is not found");
    }
    ctx->clearLeftValueFlag();
    ctx->clearStaticAccess();
    ctx->clearReceiver();
    return result;
}