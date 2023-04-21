cmake_minimum_required(VERSION 3.21)
project(llvm_oop)

set(CMAKE_CXX_STANDARD 17)

add_executable(llvm_oop main.cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_definitions(-DANTLR4CPP_STATIC)
set(ANTLR4_WITH_STATIC_CRT OFF)
set(ANTLR4_TAG 4.10.1)
include(ExternalAntlr4Cpp)
include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/lib/Parser/antlr4cpp_generated_src/LLOP)
#include_directories(/opt/homebrew/Cellar/antlr4-cpp-runtime/4.12.0/include/antlr4-runtime)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/antlr4-runtime/runtime/Cpp/runtime/src)


find_package(ANTLR)
if (NOT ANTLR_FOUND)
    set(ANTLR_JAR antlr-${ANTLR4_TAG}-complete.jar)
    set(ANTLR_JAR_URL https://www.antlr.org/download/${ANTLR_JAR})
    message(STATUS "Downloading antlr jar")
    file(DOWNLOAD ${ANTLR_JAR_URL} ${CMAKE_BINARY_DIR}/include/${ANTLR_JAR})
    message(STATUS "Downloading complete")
    set(ANTLR_EXECUTABLE ${CMAKE_BINARY_DIR}/include/${ANTLR_JAR})
    find_package(ANTLR REQUIRED)
endif ()

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(src)
add_subdirectory(lib)

target_include_directories(lib PRIVATE include)
target_include_directories(code_gen PRIVATE include)
target_include_directories(parser PRIVATE include)
target_include_directories(main PRIVATE include)
target_include_directories(ast PRIVATE include)


