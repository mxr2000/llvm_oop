//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_VARIABLEDECLSTMT_H
#define LLVM_OOP_VARIABLEDECLSTMT_H

#include "Stmt.h"
#include <string>
#include "../Type/Type.h"

class VariableDeclStmt : public Stmt {
private:
    std::string name;
    Type *type;
};

#endif //LLVM_OOP_VARIABLEDECLSTMT_H
