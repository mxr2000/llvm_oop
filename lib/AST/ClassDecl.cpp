//
// Created by Xinrun Miao on 4/4/23.
//

#include "llop/AST/AST.h"
#include <iostream>

void ClassDecl::generateInterfaceOffsetMap() {
    size_t base = parent == nullptr ? 1 : parent->Methods().size();
    if (parent != nullptr) {
        interfaceOffsetMap = parent->interfaceOffsetMap;
    }
    for (const auto &interface: implementedInterfaces) {
        interfaceOffsetMap.insert(std::make_pair(interface->Name(), base));
        base += interface->Methods().size();
    }
    for (const auto &pair: interfaceOffsetMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

void ClassDecl::buildFields(const std::vector<FieldDecl *> &newFields) {
    if (parent != nullptr) {
        fields = parent->fields;
    }
    for (const auto &field: newFields) {
        fields.push_back(field);
    }
    std::cout << "Fields for class " << name << " are:" << std::endl;
    for (const auto &field: fields) {
        std::cout << field->Name() << std::endl;
    }
    std::cout << std::endl;
}

unsigned long ClassDecl::getNewInterfaceMethodsSize() {
    unsigned long result = 0;
    for (const auto& interface : implementedInterfaces) {
        result += interface->Methods().size();
    }
    return result;
}

void ClassDecl::buildMethods(const std::vector<FuncDecl *> &newMethods) {
    if (parent != nullptr) {
        methods = parent->methods;
    }
    unsigned long parentTableSize = methods.size();

    unsigned long newInterfaceMethodsSize = getNewInterfaceMethodsSize();
    while (newInterfaceMethodsSize-- > 0) {
        methods.push_back(nullptr);
    }

    for (const auto &newMethod: newMethods) {
        if (newMethod->Header()->Name() == "init") {
            if (!methods.empty()) {
                methods[0] = newMethod;
            } else {
                methods.push_back(newMethod);
            }
            continue;
        }

        auto iter =
                std::find_if(
                        methods.begin(),
                        methods.begin() + (long) parentTableSize,
                        [&newMethod](FuncDecl *m) { return m->Header()->equals(newMethod->Header()); });
        if (iter != (methods.begin() + (long) parentTableSize)) {
            methods[iter - methods.begin()] = newMethod;
            continue;
        }
        //Not an overridden function of parent class

        bool isInterfaceMethod = false;
        for (const auto &interface: implementedInterfaces) {
            auto interfaceMethods = interface->Methods();
            auto iter = std::find_if(
                    interfaceMethods.begin(),
                    interfaceMethods.end(),
                    [&newMethod](FuncHeader *h) {return h->equals(newMethod->Header()); }
            );
            if (iter == interfaceMethods.end()) {
                continue;
            }
            int index = interfaceOffsetMap[interface->Name()] + (int) (iter - interfaceMethods.begin());
            methods[index] = newMethod;
            isInterfaceMethod = true;
            break;
        }
        if (isInterfaceMethod) {
            continue;
        }
        methods.push_back(newMethod);
    }
    std::cout << "Methods for class " << name << " are:" << std::endl;
    for (const auto &m: methods) {
        std::cout << m->Header()->toString() << std::endl;
    }
    std::cout << std::endl;
}


std::pair<int, Type *> ClassDecl::getFieldIndex(const std::string &fieldName) {
    auto iter =
            std::find_if(fields.begin(), fields.end(), [fieldName](FieldDecl* field) { return field->Name() == fieldName; });
    if (iter == fields.end()) {
        return std::make_pair(-1, nullptr);
    }
    return std::make_pair(iter - fields.begin(), (*iter)->Type());
}

int ClassDecl::getInterfaceOffset(const std::string& interName) {
    if (interfaceOffsetMap.count(interName) == 0) {
        return -1;
    }
    return interfaceOffsetMap[interName];
}

