//
// Created by Xinrun Miao on 4/19/23.
//

#include "llop/AST/AST.h"

bool FuncDecl::isLastLineReturnStmt() {
    if (block == nullptr) {
        return false;
    }
    auto stmts = block->Stmts();
    if (stmts.empty()) {
        return false;
    }
    if (!dynamic_cast<ReturnStmt*>(stmts[stmts.size() - 1])) {
        return false;
    }
    return true;
}