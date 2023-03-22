//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_PARENEXPR_H
#define LLVM_OOP_PARENEXPR_H

#include "Expr.h"

class ParenExpr : public Expr {
private:
    Expr *expr;
};

#endif //LLVM_OOP_PARENEXPR_H
