//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_PARAM_H
#define LLVM_OOP_PARAM_H

#include "../Node.h"
#include <string>
#include <utility>
#include "../Type/Type.h"

class Param : public Node {
private:
    std::string name;
    Type *type;
public:
    Param(std::string name, Type *type) : name(std::move(name)), type(type) {}

    std::string Name() { return name; }

    Type *Type() { return type; }

    GenValue *codegen(Context *ctx) override { return nullptr; }
};

#endif //LLVM_OOP_PARAM_H
