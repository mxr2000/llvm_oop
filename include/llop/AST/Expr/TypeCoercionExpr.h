//
// Created by Xinrun Miao on 4/1/23.
//

#ifndef LLVM_OOP_TYPECOERCIONEXPR_H
#define LLVM_OOP_TYPECOERCIONEXPR_H

#include "./Expr.h"
#include "../Type/SimpleType.h"

class TypeCoercionExpr : public Expr {
private:
    Expr *expr;
    ReferenceType *type;

public:
    TypeCoercionExpr(Expr *expr, ReferenceType *type) : expr(expr), type(type) {}

    Expr *getExpr() { return expr; }

    ReferenceType *getType() { return type; }

    GenValue * codegen(Context* ctx) override;
};


#endif //LLVM_OOP_TYPECOERCIONEXPR_H
