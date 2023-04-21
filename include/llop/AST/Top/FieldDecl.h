//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_FIELDDECL_H
#define LLVM_OOP_FIELDDECL_H

#include "../Node.h"
#include "../Type/Type.h"
#include <string>
#include <utility>

class FieldDecl : public Node {
private:
    Type *type;
    std::string name;

public:
    FieldDecl(std::string name, Type *type) : name(std::move(name)), type(type) {}

    std::string Name() { return name; }

    Type *Type() { return type; }

    GenValue *codegen(Context *ctx) override { return nullptr; }

};

#endif //LLVM_OOP_FIELDDECL_H
