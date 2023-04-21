//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_ASSIGNSTMT_H
#define LLVM_OOP_ASSIGNSTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class AssignStmt : public Stmt {
private:
    Expr *lhs, *rhs;
public:
    AssignStmt(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}

    Expr *Rhs() { return rhs; }

    Expr *Lhs() { return lhs; }

    GenValue * codegen(Context* ctx) override;
};

#endif //LLVM_OOP_ASSIGNSTMT_H
