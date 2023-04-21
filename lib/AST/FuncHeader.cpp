//
// Created by Xinrun Miao on 4/4/23.
//
#include "llop/AST/AST.h"
#include "llop/AST/Fragment/FuncHeader.h"


std::string FuncHeader::toString() {
    std::string result = name + "(";
    for (auto param : params) {
        result += param->Type()->toString() + " ";
    }
    result += "): ";
    return result;
}

bool FuncHeader::equals(FuncHeader *other) {
    return toString() == other->toString();
}



const std::vector<Param *> &FuncHeader::Params() const {
    return params;
}

const std::string &FuncHeader::Name() const {
    return name;
}

Type *FuncHeader::ReturnType() const {
    return returnType;
}
