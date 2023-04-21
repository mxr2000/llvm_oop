//
// Created by Xinrun Miao on 4/19/23.
//

#ifndef LLVM_OOP_VOIDTYPE_H
#define LLVM_OOP_VOIDTYPE_H

#include "Type.h"

class VoidType : public Type {
public:
    bool isVoid() override { return true; }

    GenValue *codegen(Context *ctx) override { return nullptr; }

    std::string toString() override { return "Void"; }

    bool isPointerType() override { return false; }
};


#endif //LLVM_OOP_VOIDTYPE_H

