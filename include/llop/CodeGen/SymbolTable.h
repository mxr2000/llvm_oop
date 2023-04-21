//
// Created by Xinrun Miao on 4/5/23.
//

#ifndef LLVM_OOP_SYMBOLTABLE_H
#define LLVM_OOP_SYMBOLTABLE_H

#include "GenValue.h"
#include <unordered_map>

enum SymbolTableType {
    Static,
    Class,
    Function
};


class SymbolTable {
private:
    SymbolTable *parent;
    std::unordered_map<std::string, GenValue *> valueMap;
    SymbolTableType type;

public:
    explicit SymbolTable(SymbolTable *parent, SymbolTableType type = SymbolTableType::Function) : parent(parent),
                                                                                                  type(type) {}

    void insertVariable(const std::string &name, GenValue *val);

    GenValue *findVariable(const std::string &name);

    SymbolTable *Parent() { return parent; }

    SymbolTableType Type() { return type; }
};

#endif //LLVM_OOP_SYMBOLTABLE_H
