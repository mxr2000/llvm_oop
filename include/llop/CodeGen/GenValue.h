//
// Created by Xinrun Miao on 4/5/23.
//

#ifndef LLVM_OOP_GENVALUE_H
#define LLVM_OOP_GENVALUE_H

#include "llvm/IR/Module.h"
class Type;

class GenValue {
private:
    Type *type;
    llvm::Value *value;
public:
    GenValue(Type *type, llvm::Value *value) : type(type), value(value) {}

    virtual bool isSelf() { return false; }

    virtual bool isSuper() { return false; }

    virtual bool isNull() { return false; }

    llvm::Value *Value() { return value; }

    Type *Type() { return type; }

    bool isReference();

    bool isInt();

    static GenValue *createIntGenValue(llvm::Value * val);
};

class SelfGenValue : public GenValue {
public:
    SelfGenValue(::Type *type, llvm::Value *value) : GenValue(type, value) {}

    bool isSelf() override { return true; }
};

class SuperGenValue : public GenValue {
public:
    SuperGenValue(::Type *type, llvm::Value *value) : GenValue(type, value) {}

    bool isSuper() override { return true; }
};

class NullGenValue : public GenValue {
public:
    NullGenValue() : GenValue(nullptr, nullptr) {}

    bool isNull() override { return true; }
};



#endif //LLVM_OOP_GENVALUE_H
