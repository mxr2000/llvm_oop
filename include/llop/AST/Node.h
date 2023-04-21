//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_NODE_H
#define LLVM_OOP_NODE_H

class GenValue;
class Context;

class Node {
public:
    virtual GenValue *codegen(Context* ctx) = 0;
};

#endif //LLVM_OOP_NODE_H
