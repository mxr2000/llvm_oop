//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_NEWOBJECTEXPR_H
#define LLVM_OOP_NEWOBJECTEXPR_H

#include "Expr.h"
#include "../Type/Type.h"
#include <vector>

class NewObjectExpr : public Expr {
private:
    Type *type;
    std::vector<Expr*> arguments;
};

#endif //LLVM_OOP_NEWOBJECTEXPR_H
