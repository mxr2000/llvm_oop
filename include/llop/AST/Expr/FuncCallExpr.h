//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_FUNCCALLEXPR_H
#define LLVM_OOP_FUNCCALLEXPR_H

#include "Expr.h"
#include <utility>
#include <vector>

class FuncCallExpr : public Expr {
private:
    std::string name;
    std::vector<Expr *> arguments;
public:
    FuncCallExpr(std::string name, std::vector<Expr *> arguments) : name(std::move(name)),
                                                                    arguments(std::move(arguments)) {}

    std::string getName() { return name; }

    std::vector<Expr *> getArguments() { return arguments; }
};

#endif //LLVM_OOP_FUNCCALLEXPR_H
