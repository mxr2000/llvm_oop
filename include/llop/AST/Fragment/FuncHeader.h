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
    std::vector<Param *> params;
    std::string name;
    Type *returnType;
public:
    FuncHeader(std::string name, std::vector<Param *> params, Type *returnType)
            : name(std::move(name)), params(std::move(params)), returnType(returnType) {}

    GenValue *codegen(Context *ctx) override { return nullptr; }

    std::string toString();

    bool equals(FuncHeader *other);

    std::string Name() { return name; }

    const std::vector<Param *> &Params() const;

    Type *ReturnType() const;

    const std::string &Name() const;
};

#endif //LLVM_OOP_FUNCHEADER_H
