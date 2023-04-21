//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_WHILESTMT_H
#define LLVM_OOP_WHILESTMT_H

#include "Stmt.h"
#include "../Expr/Expr.h"

class WhileStmt : public Stmt {
private:
    Expr *condition;
    Stmt *body;
public:
    WhileStmt(Expr *condition, Stmt *body) : condition(condition), body(body) {}

    GenValue *codegen(Context *ctx) override;

    Expr *Condition() { return condition; }

    Stmt *Body() { return body; }
};

#endif //LLVM_OOP_WHILESTMT_H
