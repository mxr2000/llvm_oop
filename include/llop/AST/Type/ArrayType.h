//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_ARRAYTYPE_H
#define LLVM_OOP_ARRAYTYPE_H

#include "ReferenceType.h"

class ArrayType : public ReferenceType {
private:
    Type *subType;
public:
    explicit ArrayType(Type *subType) : subType(subType) {}

    Type *getSubType() { return subType; }
};

#endif //LLVM_OOP_ARRAYTYPE_H
