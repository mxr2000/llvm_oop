//
// Created by Xinrun Miao on 4/2/23.
//


#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"


GenValue *VariableExpr::codegen(Context *ctx) {
    // load pointer when it is in left value and top level access
    bool loadPointer = ctx->LeftValueFlag() && ctx->TopLevelAccess();
    if (Name() == "food" && !ctx->LeftValueFlag()) {
        loadPointer = loadPointer;
    }
    if (ctx->Receiver() == nullptr) {
        GenValue* variable = ctx->findVariable(Name());
        if (variable != nullptr) {
            // We found a local variable, return
            return loadPointer ? variable : ctx->getLoadedValue(variable);
        }
    }

    std::pair<int, ::Type*> field;
    GenValue* receiver{};

    // The receiver is null of self
    if (ctx->Receiver() == nullptr || ctx->Receiver()->isSelf()) {
        field = ctx->getFieldRuntime(Name());
        receiver = ctx->Self();
    } else {
        // The receiver is not null(an object)
        field = ctx->getFieldRuntime(Name(), ctx->Receiver()->Type());
        receiver = ctx->Receiver();
    }
    if (field.second == nullptr) {
        throw std::runtime_error("Field or variable: " + Name() + " cannot be found");
    }
    Value *address = ctx->Builder().CreateStructGEP(
            ctx->getStructType(receiver->Type()->toString()),
            receiver->Value(),
            field.first
    );
    auto* pointer = new GenValue(field.second, address);
    return loadPointer ? pointer : ctx->getLoadedValue(pointer);
}