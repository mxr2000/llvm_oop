//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_PROGRAM_H
#define LLVM_OOP_PROGRAM_H

#include "../Node.h"
#include <vector>
#include "ClassDecl.h"
#include "InterfaceDecl.h"
#include "StaticDecl.h"

class Program : public Node {
private:
    std::vector<ClassDecl*> classDecls;
    std::vector<InterfaceDecl*> interfaceDecls;
    std::vector<StaticDecl*> staticDecls;
};

#endif //LLVM_OOP_PROGRAM_H
