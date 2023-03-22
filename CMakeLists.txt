cmake_minimum_required(VERSION 3.21)
project(llvm_oop)

set(CMAKE_CXX_STANDARD 14)

add_executable(llvm_oop main.cpp)




add_subdirectory(src)
add_subdirectory(lib)

target_include_directories(ast PRIVATE include)
target_include_directories(code_gen PRIVATE include)
target_include_directories(parser PRIVATE include)
