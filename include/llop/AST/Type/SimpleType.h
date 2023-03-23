//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_SIMPLETYPE_H
#define LLVM_OOP_SIMPLETYPE_H

#include "ReferenceType.h"
#include <string>

class SimpleType : public ReferenceType {
private:
    std::string name;
public:
    explicit SimpleType(std::string name) : name(name) {}

    std::string getName() { return name; }
};

#endif //LLVM_OOP_SIMPLETYPE_H
