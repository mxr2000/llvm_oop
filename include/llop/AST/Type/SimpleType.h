//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_SIMPLETYPE_H
#define LLVM_OOP_SIMPLETYPE_H
#include "Type.h"
#include <string>
class SimpleType : public Type {
private:
    std::string name;
};
#endif //LLVM_OOP_SIMPLETYPE_H
