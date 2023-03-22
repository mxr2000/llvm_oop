//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_CLASSRUNTIME_H
#define LLVM_OOP_CLASSRUNTIME_H

#include <utility>

class ClassRuntime {
public:
    /**
     * return the function's index in the function table, as well as its type
     * @param name function name
     * @return
     */
    std::pair<int, void*> getMethod(std::string name);

    /**
     *
     * @param name
     * @return
     */
    std::pair<int, void*> getField(std::string name);
};


#endif //LLVM_OOP_CLASSRUNTIME_H
