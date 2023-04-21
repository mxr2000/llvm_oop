add_library(lib)
target_sources(lib PUBLIC Compiler.cpp)

add_subdirectory(AST)
add_subdirectory(CodeGen)
add_subdirectory(Parser)

target_link_libraries(lib PRIVATE ${llvm_libs} ast code_gen parser)
