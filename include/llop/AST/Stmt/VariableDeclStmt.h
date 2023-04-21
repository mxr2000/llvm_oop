//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_VARIABLEDECLSTMT_H
#define LLVM_OOP_VARIABLEDECLSTMT_H

#include "Stmt.h"
#include <string>
#include <utility>
#include "../Type/Type.h"

class VariableDeclStmt : public Stmt {
private:
    std::string name;
    Type *type;
public:
    VariableDeclStmt(std::string name, Type *type) : name(std::move(name)), type(type) {}

    std::string Name() { return name; }

    Type *Type() { return type; }

    GenValue * codegen(Context *ctx) override;
};

#endif //LLVM_OOP_VARIABLEDECLSTMT_H
