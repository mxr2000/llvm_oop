//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_VALUETYPE_H
#define LLVM_OOP_VALUETYPE_H

#include "Type.h"
#include <string>

class ValueType : public Type {
private:
    std::string name;
public:
    explicit ValueType(std::string name) : name(name) {}

    std::string getName() { return name; }

    bool isPointerType() override { return false; }
};

#endif //LLVM_OOP_VALUETYPE_H
