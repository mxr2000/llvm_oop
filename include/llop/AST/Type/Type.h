//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_TYPE_H
#define LLVM_OOP_TYPE_H

#include <string>
#include "llop/AST/Node.h"

class Type : public Node {
public:
    virtual bool isPointerType() = 0;

    virtual std::string toString() = 0;

    virtual bool isVoid() { return false; }
};

#endif //LLVM_OOP_TYPE_H
