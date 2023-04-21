//
// Created by Xinrun Miao on 4/5/23.
//

#ifndef LLVM_OOP_STATICACCESSEXPR_H
#define LLVM_OOP_STATICACCESSEXPR_H

#include "Expr.h"

class StaticAccessExpr : public Expr {
private:
    Expr *expr;
    ReferenceType *type;
public:
    StaticAccessExpr(Expr *expr, ReferenceType *type) : expr(expr), type(type) {}

    Expr *Expr() { return expr; }

    ReferenceType *Type() { return type; }

    GenValue *codegen(Context *ctx) override;
};

#endif //LLVM_OOP_STATICACCESSEXPR_H
