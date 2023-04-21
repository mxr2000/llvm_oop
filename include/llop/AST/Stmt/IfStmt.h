//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_IFSTMT_H
#define LLVM_OOP_IFSTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class IfStmt : public Stmt {
private:
    Expr *condition;
    Stmt *thenStmt;
    Stmt *elseStmt;
public:
    IfStmt(Expr *Condition, Stmt *thenStmt, Stmt *elseStmt) : condition(Condition), thenStmt(thenStmt),
                                                              elseStmt(elseStmt) {}

    Expr *Condition() { return condition; }

    Stmt *ThenStmt() { return thenStmt; }

    Stmt *ElseStmt() { return elseStmt; }

    GenValue * codegen(Context* ctx) override;
};

#endif //LLVM_OOP_IFSTMT_H
