//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_CLASSDECL_H
#define LLVM_OOP_CLASSDECL_H

#include "../Node.h"
#include "FieldDecl.h"
#include "FuncDecl.h"
#include <vector>
class ClassDecl : public Node {
private:
    std::vector<FieldDecl*> fields;
    std::vector<FuncDecl*> methods;

};

#endif //LLVM_OOP_CLASSDECL_H
