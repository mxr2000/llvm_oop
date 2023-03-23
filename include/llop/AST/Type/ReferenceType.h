//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_REFERENCETYPE_H
#define LLVM_OOP_REFERENCETYPE_H
#include "Type.h"
class ReferenceType : public Type {
public:
    bool isPointerType() override { return true; }
};

#endif //LLVM_OOP_REFERENCETYPE_H
