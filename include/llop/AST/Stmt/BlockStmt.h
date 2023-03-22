//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_BLOCKSTMT_H
#define LLVM_OOP_BLOCKSTMT_H

#include "Stmt.h"
#include <vector>

class BlockStmt : public Stmt {
private:
    std::vector<Stmt*> stmts;
};

#endif //LLVM_OOP_BLOCKSTMT_H
