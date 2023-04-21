//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_VARIABLEEXPR_H
#define LLVM_OOP_VARIABLEEXPR_H

#include "Expr.h"
#include <string>
class VariableExpr : public Expr {
private:
    std::string name;

public:
    explicit VariableExpr(std::string name) : name(std::move(name)) {}

    std::string Name() { return name; }

    GenValue * codegen(Context* ctx) override;
};

#endif //LLVM_OOP_VARIABLEEXPR_H
