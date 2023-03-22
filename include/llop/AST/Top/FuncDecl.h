//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_FUNCDECL_H
#define LLVM_OOP_FUNCDECL_H

#include "../Node.h"
#include "../Fragment/FuncHeader.h"
#include "../Stmt/BlockStmt.h"

class FuncDecl : public Node {
private:
    FuncHeader* header;
    BlockStmt* block;
};

#endif //LLVM_OOP_FUNCDECL_H
