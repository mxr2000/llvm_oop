//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_INTERFACEDECL_H
#define LLVM_OOP_INTERFACEDECL_H

#include "../Node.h"
#include "../Fragment/FuncHeader.h"
#include <utility>
#include <vector>
#include <string>

class InterfaceDecl : public Node {
private:
    std::string name;
    std::vector<FuncHeader *> methods;
    std::vector<InterfaceDecl *> extendedInterfaces;
public:
    InterfaceDecl(std::string name, std::vector<FuncHeader *> methods,
                  std::vector<InterfaceDecl *> extendedInterfaces) : name(std::move(name)), methods(std::move(methods)),
                                                                     extendedInterfaces(
                                                                             std::move(extendedInterfaces)) {}

    std::string Name() { return name; }

    std::vector<InterfaceDecl *> ExtendedInterfaces() { return extendedInterfaces; }

    std::vector<FuncHeader *> Methods() { return methods; }

    GenValue * codegen(Context *ctx) override;
};

#endif //LLVM_OOP_INTERFACEDECL_H
