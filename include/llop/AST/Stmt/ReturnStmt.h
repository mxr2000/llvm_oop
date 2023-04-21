//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_RETURNSTMT_H
#define LLVM_OOP_RETURNSTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class ReturnStmt : public Stmt {
private:
    Expr *expr;
public:
    explicit ReturnStmt(Expr *expr) : expr(expr) {}

    Expr *Expr() { return expr; }

    GenValue *codegen(Context* ctx) override;
};

#endif //LLVM_OOP_RETURNSTMT_H
