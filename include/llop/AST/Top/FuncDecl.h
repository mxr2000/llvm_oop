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
    FuncHeader *header{};
    BlockStmt *block{};
public:
    FuncHeader *Header() { return header; }

    BlockStmt *Block() { return block; }

    FuncDecl(FuncHeader *header, BlockStmt *block) : header(header), block(block) {}

    GenValue * codegen(Context *ctx) override;

    bool isLastLineReturnStmt();
};

#endif //LLVM_OOP_FUNCDECL_H
