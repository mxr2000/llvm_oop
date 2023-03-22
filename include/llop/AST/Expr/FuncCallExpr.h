//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_FUNCCALLEXPR_H
#define LLVM_OOP_FUNCCALLEXPR_H

#include "Expr.h"
#include <vector>
class FuncCallExpr : public Expr {
private:
    Expr *func;
    std::vector<Expr*> arguments;
};

#endif //LLVM_OOP_FUNCCALLEXPR_H
