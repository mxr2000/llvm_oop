//
// Created by Xinrun Miao on 4/2/23.
//

#include "llop/CodeGen/Context.h"
#include "llop/AST/Top/Program.h"
#include <iostream>

void Context::buildParentTable() {
    for (auto decl: program->Classes()) {
        auto cur = decl.second->Parent();
        while (cur != nullptr) {
            parentTable[decl.first].push_back(cur->Name());
            cur = cur->Parent();
        }
    }
}

void Context::buildIndexTable() {
    int id = 0;
    for (const auto& decl: program->Classes()) {
        setClassIndex(decl.first, id++);
    }
}

Context::Context(Program *program) : builder(TheContext), TheModule("demo", TheContext) {
    Triple targetTriple(sys::getDefaultTargetTriple());
    TheModule.setTargetTriple(targetTriple.str());
    this->program = program;
    OneInt = createConstantInt(0);
    ZeroInt = createConstantInt(1);
    IntType = llvm::Type::getInt32Ty(TheContext);

    BooleanType = llvm::Type::getInt1Ty(TheContext);
    OneBoolean = ConstantInt::get(BooleanType, 1);
    ZeroBoolean = ConstantInt::get(BooleanType, 0);


    FunPtrType = PointerType::get(
            FunctionType::get(IntType, std::vector<llvm::Type *>(), false), 0);
    IntPtrType = llvm::PointerType::get(IntType, 0);

    std::vector<llvm::Type *> twoInt(2, IntType);
    CallocFunction = llvm::Function::Create(
            FunctionType::get(IntPtrType, twoInt, false), llvm::Function::ExternalLinkage,
            "calloc", TheModule);
    OutputFunction = llvm::Function::Create(
            FunctionType::get(llvm::Type::getVoidTy(TheContext), IntType, false), llvm::Function::ExternalLinkage,
            "output", TheModule
    );

    buildIndexTable();
    buildParentTable();
    generateVirtualTable();
    generateStructs();
    program->codegen(this);
    generateInterfaceOffsetTable();
}

void Context::pushSymbolTable() {
    curTable = new SymbolTable(curTable);
}

void Context::popSymbolTable() {
    curTable = curTable->Parent();
}

void Context::generateVirtualTable() {
    for (const auto &pair: program->Classes()) {
        auto name = pair.first;
        auto decl = pair.second;
        int len = decl->Methods().size() + 2;
        vtableTypes[name] = ArrayType::get(FunPtrType, len);
        vtableInitializers[name] = std::vector<Constant *>(len);
        vtables.insert(std::make_pair(name, createVTable("vtable_" + name, vtableTypes[name], len)));
    }
}

void Context::generateInterfaceOffsetTable() {
    int len = program->Classes().size();
    for (const auto &pair: program->Interfaces()) {
        auto tableType = ArrayType::get(IntType, len);
        std::vector<Constant *> arr(len, nullptr);
        for (auto classPair: program->Classes()) {
            auto classIndex = classIndexes[classPair.first];
            auto offset = classPair.second->getInterfaceOffset(pair.first) + 2;
            arr[classIndex] = ConstantInt::get(IntType, offset);
        }
        auto type = ArrayType::get(IntType, len);
        auto variable = new GlobalVariable(TheModule, tableType, true,
                                           llvm::GlobalValue::InternalLinkage,
                                           ConstantArray::get(type, arr), pair.first);
        interfaceOffsetTable[pair.first] = variable;
    }
}

void Context::generateStructs() {
    for (const auto &pair: program->Classes()) {
        auto name = pair.first;
        auto decl = pair.second;
        size_t len = decl->Methods().size() + 2;
        std::vector<llvm::Type *> structFields;
        structFields.push_back(PointerType::get(ArrayType::get(IntPtrType, len), 0));
        for (auto field: decl->Fields()) {
            if (field->Type()->isPointerType()) {
                structFields.push_back(IntPtrType);
            } else {
                structFields.push_back(IntType);
            }
        }
        auto *type = StructType::create(TheContext, structFields, "struct_" + name, true);
        classStructs[name] = type;
    }
}

Value *Context::createConstantInt(int val) {
    return ConstantInt::get(llvm::Type::getInt64Ty(TheContext), val);
}

GlobalVariable *Context::createVTable(const std::string &name, ArrayType *tableType, int len) {
    return new GlobalVariable(TheModule, tableType, true,
                              llvm::GlobalValue::InternalLinkage,
                              nullptr, name);
}

std::pair<int, ::Type *> Context::getFieldRuntime(const std::string &name, ::Type* type) {
    ClassDecl* decl = type == nullptr ? curClass : program->Classes()[type->toString()];
    if (decl == nullptr) {
        throw std::runtime_error("cannot find runtime field of " + name);
    }
    auto original = decl->getFieldIndex(name);
    return std::make_pair(original.first + 1, original.second); // The first one is the pointer to vtable
}

GenValue *Context::findVariable(const std::string &name) {
    SymbolTable *cur = curTable;
    while (cur != nullptr) {
        auto result = cur->findVariable(name);
        if (result != nullptr) {
            return result;
        }
        cur = cur->Parent();
    }
    return nullptr;
}

GenValue *Context::findParam(const std::string &name) {
    SymbolTable *cur = curTable;
    while (cur->Parent() != nullptr) {
        cur = cur->Parent();
    }
    return cur->findVariable(name);
}


void Context::addValueToCurrentTable(const std::string &name, GenValue *value) {
    if (curTable == nullptr) {
        throw std::runtime_error("Current symbol table is null");
    }
    curTable->insertVariable(name, value);
}

std::pair<llvm::Function *, FuncHeader *>
Context::findCalledStaticFunction(const std::string &name, const std::vector<GenValue *> &params) {
    std::string staticName;
    if (staticAccessClass != nullptr) {
        staticName = staticAccessClass->toString();
    } else if (curStatic != nullptr) {
        staticName = curStatic->Name();
    } else {
        return std::make_pair(nullptr, nullptr);
    }
    auto staticDecl = program->Statics()[staticName];
    auto methods = staticDecl->Methods();
    auto iter = std::find_if(methods.begin(), methods.end(),
                             [this, &params, &name](FuncDecl *m) { return m->Header()->Name() == name && isFunctionType(params, m->Header()); });
    if (iter == methods.end()) {
        return std::make_pair(nullptr, nullptr);
    }
    auto header = (*iter)->Header();
    return std::make_pair(staticFunctions[getStaticMethodSignature(staticDecl, header)], header);
}

std::pair<int, FuncHeader *>
Context::findCalledClassMethod(::Type *classType, const std::string &name, const std::vector<GenValue *> &params) {
    auto classDecl = program->Classes()[classType->toString()];
    auto methods = classDecl->Methods();
    auto iter = std::find_if(methods.begin(), methods.end(),
                             [this, &params, &name](FuncDecl *m) {
                                 return name == m->Header()->Name() && isFunctionType(params, m->Header());
                             });
    if (iter == methods.end()) {
        return std::make_pair(-1, nullptr);
    }
    return std::make_pair(iter - methods.begin(), (*iter)->Header());
}

FuncHeader *Context::getMethodHeader(::Type *classType, int index) {
    return program->Classes()[classType->toString()]->Methods()[index]->Header();
}


llvm::StructType *Context::getStructType(const std::string &name) {
    return classStructs[name];
}

llvm::BasicBlock *Context::createBasicBlock(const std::string &name) {
    if (curFunction == nullptr) {
        throw std::runtime_error("not in a function scope");
    }
    return BasicBlock::Create(TheContext, name, curFunction);
}

GenValue *Context::Super() {
    auto self = Self();
    return new SuperGenValue(curClass->Parent()->Type(), self->Value());
}

GenValue *Context::Self() {
    return new SelfGenValue(curClass->Type(), CurFunction()->args().begin());
}

llvm::Function *Context::createCurFunction(FuncHeader *header) {
    if (IsInStaticMethod()) {
        throw std::runtime_error("Static method should not call this function");
    }
    return Function::Create(
            headerToLlvmType(header, !IsInStaticMethod()),
            Function::ExternalLinkage,
            getMethodSignature(curStatic == nullptr ? curClass->Name() : curStatic->Name(), header),
            TheModule);
}

void Context::createStaticFunction(const std::string &staticName, FuncHeader *header) {
    auto fName = getMethodSignature(staticName, header);
    auto f = Function::Create(
            headerToLlvmType(header, false),
            Function::ExternalLinkage,
            fName,
            TheModule);
    staticFunctions[fName] = f;
}

bool Context::isSubType(::Type *sub, ::Type *parent) {
    if (sub->toString() == parent->toString()) {
        return true;
    }
    auto beExtended = parentTable[sub->toString()];
    return std::find(beExtended.begin(), beExtended.end(), parent->toString()) != beExtended.end();
}

bool Context::isFunctionType(const std::vector<GenValue *> &args, FuncHeader *header) {
    auto params = header->Params();
    if (args.size() != params.size()) {
        return false;
    }
    for (int i = 0; i < args.size(); i++) {
        if (!args[i]->Type()->isPointerType() && args[i]->Type()->toString() != params[i]->Type()->toString()) {
            std::cout << "should not be here 1" << std::endl;
            return false;
        }
        if (args[i]->Type()->isPointerType() && !isSubType(args[i]->Type(), params[i]->Type())) {
            std::cout << "should not be here 2" << std::endl;
            return false;
        }
    }
    return true;
}

void Context::insertIntoVTableInitializer(const std::string &className, int index, llvm::Function *f) {
    vtableInitializers[className][index] = f;
}

void Context::buildVTable(ClassDecl *decl) {
    auto name = decl->Name();
    auto arr = vtableInitializers[name];
    arr[0] = new GlobalVariable(
            TheModule,
            llvm::Type::getInt32Ty(TheContext),
            true,
            llvm::GlobalValue::InternalLinkage,
            ConstantInt::get(IntType, classIndexes[name]),
            "id_" + name
    );

    if (decl->Parent() == nullptr) {
        arr[1] = vtables[name];
    } else {
        arr[1] = vtables[decl->Parent()->Name()];
    }
    auto type = ArrayType::get(IntPtrType, decl->Methods().size() + 2);
    vtables[name]->setInitializer(ConstantArray::get(type, arr));
}

uint64_t Context::getStructSize(const std::string &name) {
    auto classStruct = classStructs[name];
    return TheModule.getDataLayout().getStructLayout(classStruct)->getSizeInBytes();
}

GlobalVariable *Context::getVtable(const std::string &name) {
    return vtables[name];
}

std::string Context::getMethodSignature(const std::string &receiverClassName, FuncHeader *header) {
    if (header->Name() == "main") {
        return "main";
    }
    auto result = receiverClassName + "_" + header->Name();
    for (auto param: header->Params()) {
        result += "_";
        result += param->Type()->toString();
    }
    return result;
}

std::string Context::getClassMethodSignature(ClassDecl *classDecl, int index) {
    return getMethodSignature(classDecl->Name(), classDecl->Methods()[index]->Header());
}

std::string Context::getStaticMethodSignature(StaticDecl *staticDecl, FuncHeader *header) {
    return getMethodSignature(staticDecl->Name(), header);
}

void Context::output(const std::string &name) {
    std::error_code ec;
    ToolOutputFile result(name + ".ll", ec, sys::fs::OF_None);
    TheModule.print(result.os(), nullptr);
    result.keep();
}

llvm::FunctionType *Context::headerToLlvmType(FuncHeader *header, bool isClassMethod) {
    llvm::Type *returnType = nullptr;
    if (header->ReturnType()->isVoid()) {
        returnType = llvm::Type::getVoidTy(TheContext);
    } else if (header->ReturnType()->isPointerType()) {
        returnType = IntPtrType;
    } else {
        returnType = IntType;
    }
    std::vector<llvm::Type *> argTypes;
    if (isClassMethod) {
        argTypes.push_back(IntPtrType);
    }
    for (auto param: header->Params()) {
        argTypes.push_back(param->Type()->isPointerType() ? IntPtrType : IntType);
    }
    auto ft = llvm::FunctionType::get(returnType, argTypes, false);
    return ft;
}

llvm::Function* Context::getStaticMethod(FuncHeader* header) {
    auto fName = getStaticMethodSignature(curStatic, header);
    return staticFunctions[fName];
}

