//
// Created by Xinrun Miao on 4/2/23.
//

#ifndef LLVM_OOP_CONTEXT_H
#define LLVM_OOP_CONTEXT_H

#include "SymbolTable.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TypeSize.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include "llop/AST/Top/Program.h"
#include "llop/AST/Type/ValueType.h"

using namespace llvm;

class Context {
private:
    LLVMContext TheContext;
    Module TheModule;
    IRBuilder<> builder;

    Program *program;
    std::unordered_map<std::string, GlobalVariable *> vtables;
    std::unordered_map<std::string, std::vector<Constant *>> vtableInitializers;
    std::unordered_map<std::string, StructType *> classStructs;
    std::unordered_map<std::string, std::vector<std::string>> parentTable;
    std::unordered_map<std::string, int> classIndexes;
    std::unordered_map<std::string, llvm::Function *> staticFunctions;
    std::unordered_map<std::string, llvm::ArrayType *> vtableTypes;
    std::unordered_map<std::string, GlobalVariable *> interfaceOffsetTable;

    SymbolTable *curTable{};
    ClassDecl *curClass{};
    StaticDecl *curStatic{};

    llvm::Function *curFunction{};

    bool leftValueFlag = false;
    ::Type *staticAccessClass{};
    GenValue *receiver{};
    int accessLevel = 0;

    void generateVirtualTable();

    void generateInterfaceOffsetTable();

    void generateStructs();

    //void buildStruct(ClassDecl *decl);

    void buildParentTable();

    void buildIndexTable();

    static std::string getMethodSignature(const std::string &receiverClassName, FuncHeader *header);

public:
    explicit Context(Program *program);

    //bool areTypeCompatible(Ty)
    IRBuilder<> &Builder() { return builder; }

    Value *createConstantInt(int val);

    GlobalVariable *createVTable(const std::string &name, llvm::ArrayType *tableType, int len);

    Value *ZeroInt;

    Value *OneInt;

    Value *ZeroBoolean;

    Value *OneBoolean;

    std::unordered_map<::BasicType, llvm::Type*> BasicTypes;

    llvm::Type *BooleanType;

    llvm::Type *IntType;

    llvm::PointerType *IntPtrType;

    llvm::Type *FunPtrType;

    std::unordered_map<FuncDecl *, llvm::Function *> GeneratedFunctions; // Functions already generates


    void pushSymbolTable();

    void popSymbolTable();

    GenValue *findVariable(const std::string &name);

    GenValue *findParam(const std::string &name);

    GenValue *Super();

    GenValue *Self();

    std::pair<int, ::Type *> getFieldRuntime(const std::string &name, ::Type* type = nullptr);

    std::pair<int, FuncHeader *>
    findCalledClassMethod(::Type *classType, const std::string &name, const std::vector<GenValue *> &params);

    FuncHeader *getMethodHeader(::Type *classType, int index);

    // If static access class is set, go to find that static
    // Else, if in static scope, find method in current static decl
    // Else if in class scope, find method in static decl with the same name of class
    std::pair<llvm::Function *, FuncHeader *>
    findCalledStaticFunction(const std::string &name, const std::vector<GenValue *> &params);

    llvm::Function* getStaticMethod(FuncHeader* header);

    void addValueToCurrentTable(const std::string &name, GenValue *value);

    llvm::StructType *getStructType(const std::string &name);

    llvm::Function *CallocFunction;

    llvm::Function *OutputFunction;

    llvm::BasicBlock *createBasicBlock(const std::string &name);

    bool LeftValueFlag() const { return leftValueFlag; }

    void clearLeftValueFlag() { leftValueFlag = false; }

    void setLeftValueFlag() { leftValueFlag = true; }

    bool IsInStaticMethod() const { return curStatic != nullptr; }

    GenValue *Receiver() { return receiver; }

    void setReceiver(GenValue *r) { this->receiver = r; }

    void clearReceiver() { this->receiver = nullptr; }

    ::Type *StaticAccessClass() const { return staticAccessClass; }

    void clearStaticAccess() { staticAccessClass = nullptr; }

    void setStaticAccess(::Type *type) { staticAccessClass = type; }

    llvm::Function *createCurFunction(FuncHeader *header);

    void setCurFunction(llvm::Function *f) { curFunction = f; }

    ClassDecl *CurClass() { return curClass; }

    llvm::Function *CurFunction() { return curFunction; }

    void setCurClass(ClassDecl *decl) { curClass = decl; }

    void setCurStatic(StaticDecl *decl) { curStatic = decl; }

    void clearCurClass() { curClass = nullptr; }

    void clearCurStatic() { curStatic = nullptr; }

    bool isSubType(::Type *sub, ::Type *parent);

    bool isFunctionType(const std::vector<GenValue *> &args, FuncHeader *header);

    std::string getClassMethodSignature(ClassDecl *classDecl, int index);

    std::string getStaticMethodSignature(StaticDecl *staticDecl, FuncHeader *header);

    void insertIntoVTableInitializer(const std::string &className, int index, llvm::Function *f);

    void buildVTable(ClassDecl *decl);

    bool TopLevelAccess() const { return accessLevel == 0; }

    void incrementAccessLevel() { ++accessLevel; }

    void decrementLevelAccess() { --accessLevel; }

    GlobalVariable *getVtable(const std::string &name);

    uint64_t getStructSize(const std::string &name);

    uint64_t getValueSize(ValueType* type);

    uint64_t getPointerSize();

    void output(const std::string &name);

    llvm::FunctionType *headerToLlvmType(FuncHeader *header, bool isClassMethod);

    llvm::ArrayType *getVtableType(const std::string &name) { return vtableTypes[name]; }

    void setClassIndex(const std::string& name, int index) { classIndexes[name] = index; }

    void createStaticFunction(const std::string& staticName, FuncHeader *header);

    GenValue *getLoadedValue(GenValue *variable);
};


#endif //LLVM_OOP_CONTEXT_H
