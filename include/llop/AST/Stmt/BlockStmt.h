//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_BLOCKSTMT_H
#define LLVM_OOP_BLOCKSTMT_H

#include "Stmt.h"
#include <utility>
#include <vector>

class BlockStmt : public Stmt {
private:
    std::vector<Stmt *> stmts;
public:
    explicit BlockStmt(std::vector<Stmt *> stmts) : stmts(std::move(stmts)) {}

    std::vector<Stmt *> Stmts() { return stmts; }

    GenValue *codegen(Context* ctx) override;
};

#endif //LLVM_OOP_BLOCKSTMT_H
