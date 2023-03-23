//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_CLASSDECL_H
#define LLVM_OOP_CLASSDECL_H

#include "../Node.h"
#include "FieldDecl.h"
#include "FuncDecl.h"
#include "InterfaceDecl.h"
#include <vector>
#include <string>

class ClassDecl : public Node {
private:
    std::string name;
    ClassDecl *parent;
    std::vector<InterfaceDecl *> implementedInterfaces;
    std::vector<FieldDecl *> fields;
    std::vector<FuncDecl *> methods;
public:
    ClassDecl(std::string name) : name(std::move(name)) {}

    void setFields(std::vector<FieldDecl *> fields) { this->fields = fields; }

    void setMethods(std::vector<FuncDecl *> methods) { this->methods = methods; }

    void setParent(ClassDecl *parent) { this->parent = parent; }

    void setImplementedInterfaces(std::vector<InterfaceDecl *> interfaces) { this->implementedInterfaces = interfaces; }
};

#endif //LLVM_OOP_CLASSDECL_H
