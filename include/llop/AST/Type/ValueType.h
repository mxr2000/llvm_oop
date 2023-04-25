//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_VALUETYPE_H
#define LLVM_OOP_VALUETYPE_H

#include "Type.h"
#include <string>
#include <utility>

enum BasicType {
    Int, Char, Long, Bool
};

class ValueType : public Type {
private:
    std::string name;
public:
    explicit ValueType(std::string name) : name(std::move(name)) {}

    std::string Name() { return name; }

    bool isPointerType() override { return false; }

    std::string toString() override { return Name(); }

    GenValue *codegen(Context *ctx) override { return nullptr; }
};

#endif //LLVM_OOP_VALUETYPE_H
