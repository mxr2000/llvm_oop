//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_ACCESSEXPR_H
#define LLVM_OOP_ACCESSEXPR_H

#include "Expr.h"
#include <string>

class AccessExpr : public Expr {
private:
    std::string name;
    Expr *rhs;

public:
    AccessExpr(std::string name, Expr *rhs) : name(std::move(name)), rhs(rhs) {}

    std::string getName() { return name; }

    Expr *getRhs() { return rhs; }
};

#endif //LLVM_OOP_ACCESSEXPR_H
