//
// Created by Xinrun Miao on 4/1/23.
//

#ifndef LLVM_OOP_TYPECOERCIONEXPR_H
#define LLVM_OOP_TYPECOERCIONEXPR_H

#include "./Expr.h"
#include "../Type/SimpleType.h"

class TypeCoercionExpr : Expr {
private:
    Expr *expr;
    SimpleType *type;

public:
    TypeCoercionExpr(Expr *expr, SimpleType *type) : expr(expr), type(type) {}

    Expr *getExpr() { return expr; }

    SimpleType *getType() { return type; }
};


#endif //LLVM_OOP_TYPECOERCIONEXPR_H
