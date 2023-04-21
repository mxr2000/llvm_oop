//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_STATICDECL_H
#define LLVM_OOP_STATICDECL_H

#include "../Node.h"
#include "FuncDecl.h"
#include <utility>
#include <vector>
#include <string>

class StaticDecl : public Node {
private:
    std::string name;
    std::vector<FuncDecl *> methods;
public:
    StaticDecl(std::string name,
               std::vector<FuncDecl *> methods) : name(std::move(name)), methods(std::move(methods)) {}

    std::string Name() { return name; }

    std::vector<FuncDecl *> Methods() { return methods; }

    GenValue * codegen(Context *ctx) override;

    void createFunctions(Context *ctx);
};

#endif //LLVM_OOP_STATICDECL_H
