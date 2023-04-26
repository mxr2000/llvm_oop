//
// Created by Xinrun Miao on 4/1/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"
using namespace llvm;

GenValue *BinaryExpr::codegen(Context *ctx) {
    GenValue *l = lhs->codegen(ctx);
    GenValue *r = rhs->codegen(ctx);
    if (l == nullptr || r == nullptr) {
        throw std::runtime_error("null binary operand");
    }
    if (!l->Type()->isValueType() || !r->Type()->isValueType()) {
        throw std::runtime_error("non-value binary operand");
    }
    if (dynamic_cast<ValueType*>(l->Type())->BasicType() != dynamic_cast<ValueType*>(r->Type())->BasicType()) {
        throw std::runtime_error("operand types are different");
    }
    Value *val = nullptr;
    if (op == BinaryOp::Plus) {
        val = ctx->Builder().CreateAdd(l->Value(), r->Value(), "add_tmp");
    } else if (op == BinaryOp::Minus) {
        val = ctx->Builder().CreateSub(l->Value(), r->Value(), "sub_tmp");
    } else if (op == BinaryOp::Multiply) {
        val = ctx->Builder().CreateMul(l->Value(), r->Value(), "mul_tmp");
    } else if (op == BinaryOp::Divide) {
        val = ctx->Builder().CreateSDiv(l->Value(), r->Value(), "div_tmp");
    }
    return GenValue::createIntGenValue(val);
}
