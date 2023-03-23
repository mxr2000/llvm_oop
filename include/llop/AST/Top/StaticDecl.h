//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_STATICDECL_H
#define LLVM_OOP_STATICDECL_H

#include "../Node.h"
#include "FuncDecl.h"
#include <vector>
#include <string>

class StaticDecl : public Node {
private:
    std::string name;
    std::vector<FuncDecl*> methods;
};

#endif //LLVM_OOP_STATICDECL_H
