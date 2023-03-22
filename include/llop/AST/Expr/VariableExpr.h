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
};

#endif //LLVM_OOP_VARIABLEEXPR_H
