//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_TYPE_H
#define LLVM_OOP_TYPE_H

#include "../Node.h"

class Type : public Node {
public:
    virtual bool isPointerType() = 0;
};
#endif //LLVM_OOP_TYPE_H
