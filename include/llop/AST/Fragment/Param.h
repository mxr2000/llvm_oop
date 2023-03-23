//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_PARAM_H
#define LLVM_OOP_PARAM_H

#include "../Node.h"
#include <string>
#include "../Type/Type.h"

class Param : public Node {
private:
    std::string name;
    Type *type;
public:
    Param(std::string name, Type *type) : name(name), type(type) {}
};

#endif //LLVM_OOP_PARAM_H
