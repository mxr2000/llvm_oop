//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_CLASSDECL_H
#define LLVM_OOP_CLASSDECL_H

#include "../Node.h"
#include "FieldDecl.h"
#include "FuncDecl.h"
#include "InterfaceDecl.h"
#include "../Type/ReferenceType.h"
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

class ClassDecl : public Node {
private:
    std::string name;
    ClassDecl *parent;
    std::vector<InterfaceDecl *> implementedInterfaces;
    std::vector<FieldDecl *> fields;
    std::vector<FuncDecl *> methods;

    std::unordered_map<std::string, int> interfaceOffsetMap;

    void generateInterfaceOffsetMap();

    void buildFields(const std::vector<FieldDecl *> &newFields);

    void buildMethods(const std::vector<FuncDecl *> &newMethods);

    unsigned long getNewInterfaceMethodsSize();

public:
    ClassDecl(std::string name,
              ClassDecl *parent,
              std::vector<InterfaceDecl *> implementedInterfaces,
              const std::vector<FieldDecl *> &newFields,
              const std::vector<FuncDecl *> &newMethods) :
            name(std::move(name)),
            parent(parent),
            implementedInterfaces(std::move(implementedInterfaces)) {
        generateInterfaceOffsetMap();
        buildFields(newFields);
        buildMethods(newMethods);
    }

    GenValue *codegen(Context *ctx) override;

    std::pair<int, Type *> getFieldIndex(const std::string &name);

    std::vector<FuncDecl *> &Methods() { return methods; }

    std::vector<FieldDecl *> &Fields() { return fields; }

    std::string Name() { return name; }

    Type *Type() { return new ReferenceType(Name()); }

    ClassDecl *Parent() { return parent; }

    int getInterfaceOffset(const std::string& name);
};

#endif //LLVM_OOP_CLASSDECL_H
