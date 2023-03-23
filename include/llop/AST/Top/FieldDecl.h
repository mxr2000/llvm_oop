//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_FIELDDECL_H
#define LLVM_OOP_FIELDDECL_H

#include "../Node.h"
#include "../Type/Type.h"
#include <string>

class FieldDecl : public Node {
private:
    Type *type;
    std::string name;

public:
    FieldDecl(std::string name, Type *type) : name(name), type(type) {}

    std::string getName() { return name; }

    Type *getType() { return type; }
};

#endif //LLVM_OOP_FIELDDECL_H
