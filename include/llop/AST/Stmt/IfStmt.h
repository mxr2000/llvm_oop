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
};

#endif //LLVM_OOP_IFSTMT_H
