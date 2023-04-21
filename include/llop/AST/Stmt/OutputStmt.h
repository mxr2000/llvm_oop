//
// Created by Xinrun Miao on 4/19/23.
//

#ifndef LLVM_OOP_OUTPUTSTMT_H
#define LLVM_OOP_OUTPUTSTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class OutputStmt : public Stmt {
private:
    Expr *expr;
public:
    explicit OutputStmt(Expr *expr) : expr(expr) {}

    Expr *Expr() { return expr; }

    GenValue *codegen(Context* ctx) override;
};

#endif //LLVM_OOP_OUTPUTSTMT_H
