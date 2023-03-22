//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_ASSIGNSTMT_H
#define LLVM_OOP_ASSIGNSTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class AssignStmt : public Stmt {
private:
    Expr *lhs, rhs;
};

#endif //LLVM_OOP_ASSIGNSTMT_H
