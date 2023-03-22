//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_WHILESTMT_H
#define LLVM_OOP_WHILESTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class WhileStmt : public Stmt {
    Expr *Condition;
    Stmt *body;
};

#endif //LLVM_OOP_WHILESTMT_H
