//
// Created by Xinrun Miao on 4/5/23.
//

#include "llop/CodeGen/SymbolTable.h"


void SymbolTable::insertVariable(const std::string& name, GenValue *val) {
    valueMap.insert(std::make_pair(name, val));
}

GenValue* SymbolTable::findVariable(const std::string& name) {
    return valueMap[name];
}