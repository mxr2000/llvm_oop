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

    GenValue* generateClassMethodCall(Context* ctx, std::vector<GenValue*>& genArgs);
    GenValue* generateStaticMethodCall(Context* ctx, std::vector<GenValue*>& genArgs);
public:
    FuncCallExpr(std::string name, std::vector<Expr *> arguments) : name(std::move(name)),
                                                                    arguments(std::move(arguments)) {}

    std::string Name() { return name; }

    std::vector<Expr *> Arguments() { return arguments; }

    GenValue * codegen(Context* ctx) override;
};

#endif //LLVM_OOP_FUNCCALLEXPR_H
