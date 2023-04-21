//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_REFERENCETYPE_H
#define LLVM_OOP_REFERENCETYPE_H

#include "Type.h"


class ReferenceType : public Type {
private:
    std::string name;
public:
    explicit ReferenceType(std::string name) : name(std::move(name)) {}

    std::string Name() { return name; }

    bool isPointerType() override { return true; }

    std::string toString() override { return Name(); }

    GenValue *codegen(Context *ctx) override { return nullptr; }
};

#endif //LLVM_OOP_REFERENCETYPE_H
