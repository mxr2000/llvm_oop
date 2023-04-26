//
// Created by Xinrun Miao on 4/5/23.
//
#include "llop/CodeGen/GenValue.h"
#include "llop/AST/Type/ValueType.h"

bool GenValue::isInt() {
    return type != nullptr && type->toString() == "Int";
}

GenValue *GenValue::createIntGenValue(llvm::Value * val) {
    return new GenValue(ValueType::IntType, val);
}
