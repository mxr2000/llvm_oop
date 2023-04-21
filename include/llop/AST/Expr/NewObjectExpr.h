//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_NEWOBJECTEXPR_H
#define LLVM_OOP_NEWOBJECTEXPR_H

#include "Expr.h"
#include "../Type/ReferenceType.h"
#include <utility>
#include <vector>

class NewObjectExpr : public Expr {
private:
    ReferenceType *type;
    std::vector<Expr *> arguments;
public:
    GenValue *codegen(Context* ctx) override;

    NewObjectExpr(ReferenceType *type, std::vector<Expr *> arguments) : type(type), arguments(std::move(arguments)) {}
};

#endif //LLVM_OOP_NEWOBJECTEXPR_H
