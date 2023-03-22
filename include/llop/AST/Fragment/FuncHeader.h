//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_FUNCHEADER_H
#define LLVM_OOP_FUNCHEADER_H

#include "../Node.h"
#include "Param.h"
#include <vector>
#include <string>
class FuncHeader : public Node {
private:
    std::vector<Param*> params;
    std::string name;
};

#endif //LLVM_OOP_FUNCHEADER_H
