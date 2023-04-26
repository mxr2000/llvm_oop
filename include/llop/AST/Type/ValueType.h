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
    BasicType basicType;
public:
    explicit ValueType(BasicType type) : basicType(type) {}

    std::string Name() {
        switch (basicType) {
            case BasicType::Int:
                return "Int";
            case BasicType::Char:
                return "Char";
            case BasicType::Long:
                return "Long";
            case BasicType::Bool:
                return "Bool";
        }
        throw std::runtime_error("unknown basic type");
    }

    bool isPointerType() override { return false; }

    bool isValueType() override { return true; }

    std::string toString() override { return Name(); }

    GenValue *codegen(Context *ctx) override { return nullptr; }

    BasicType BasicType() { return basicType; }

    static ValueType *IntType;
    static ValueType *LongType;
    static ValueType *CharType;
    static ValueType *BoolType;
};

#endif //LLVM_OOP_VALUETYPE_H
