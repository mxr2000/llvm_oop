//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_IFSTMT_H
#define LLVM_OOP_IFSTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class IfStmt : public Stmt {
private:
    Expr *Condition;
    Stmt *thenStmt;
    Stmt *elseStmt;
public:
    IfStmt(Expr *Condition, Stmt *thenStmt, Stmt *elseStmt) : Condition(Condition), thenStmt(thenStmt),
                                                              elseStmt(elseStmt) {}

    Expr *getCondition() { return Condition; }

    Stmt *getThenStmt() { return thenStmt; }

    Stmt *getElseStmt() { return elseStmt; }
};

#endif //LLVM_OOP_IFSTMT_H
