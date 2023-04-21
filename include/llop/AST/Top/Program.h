//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_PROGRAM_H
#define LLVM_OOP_PROGRAM_H

#include "../Node.h"
#include <utility>
#include <vector>
#include <unordered_map>
#include "ClassDecl.h"
#include "InterfaceDecl.h"
#include "StaticDecl.h"

class Program : public Node {
private:
    std::unordered_map<std::string, ClassDecl *> classDecls;
    std::unordered_map<std::string, InterfaceDecl *> interfaceDecls;
    std::unordered_map<std::string, StaticDecl *> staticDecls;
public:
    Program(std::unordered_map<std::string, ClassDecl *> classDecls,
            std::unordered_map<std::string, InterfaceDecl *> interfaceDecls,
            std::unordered_map<std::string, StaticDecl *> staticDecls) : classDecls(std::move(classDecls)),
                                                                         interfaceDecls(std::move(interfaceDecls)),
                                                                         staticDecls(std::move(staticDecls)) {}


    GenValue *codegen(Context *ctx) override;

    std::unordered_map<std::string, ClassDecl *> &Classes() { return classDecls; }

    std::unordered_map<std::string, InterfaceDecl *> &Interfaces() { return interfaceDecls; }

    std::unordered_map<std::string, StaticDecl *> &Statics() { return staticDecls; }

};

#endif //LLVM_OOP_PROGRAM_H
