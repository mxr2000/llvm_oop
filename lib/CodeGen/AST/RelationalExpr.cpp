//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"
using namespace llvm;

GenValue *RelationalExpr::codegen(Context *ctx) {
    GenValue *l = lhs->codegen(ctx);
    GenValue *r = rhs->codegen(ctx);
    if (l == nullptr || r == nullptr) {
        throw std::runtime_error("null binary operand");
    }
    if (!l->isInt() || !r->isInt()) {
        throw std::runtime_error("non-integer binary operand");
    }
    Value *val = nullptr;
    if (op == RelationalOp::LE) {
        val = ctx->Builder().CreateICmpSLE(l->Value(), r->Value());
    } else if (op == RelationalOp::LT) {
        val = ctx->Builder().CreateICmpSLT(l->Value(), r->Value());
    } else if (op == RelationalOp::GE) {
        val = ctx->Builder().CreateICmpSGE(l->Value(), r->Value());
    } else if (op == RelationalOp::GT) {
        val = ctx->Builder().CreateICmpSGT(l->Value(), r->Value());
    } else if (op == RelationalOp::EQ) {
        val = ctx->Builder().CreateICmpEQ(l->Value(), r->Value());
    } else if (op == RelationalOp::NE) {
        val = ctx->Builder().CreateICmpNE(l->Value(), r->Value());
    }
    return GenValue::createIntGenValue(val);
}