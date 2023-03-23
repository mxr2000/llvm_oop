//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_INTERFACEDECL_H
#define LLVM_OOP_INTERFACEDECL_H

#include "../Node.h"
#include "../Fragment/FuncHeader.h"
#include <vector>
#include <string>

class InterfaceDecl : public Node {
private:
    std::string name;
    std::vector<FuncHeader*> methods;
    std::vector<InterfaceDecl*> extendedInterfaces;
};

#endif //LLVM_OOP_INTERFACEDECL_H
