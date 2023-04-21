
antlr_target(LLOPGrammar LLOP.g4 VISITOR)

set_property(GLOBAL PROPERTY GrammarIncludeDir ${ANTLR_LLOPGrammar_OUTPUT_DIR})

add_library(antlrgen STATIC ${ANTLR_LLOPGrammar_CXX_OUTPUTS} Parser.cpp)

target_link_libraries(antlrgen PRIVATE antlr4_static)

add_library(parser)
target_sources(parser PRIVATE
        ASTBuilder.cpp)
target_link_libraries(parser PRIVATE antlrgen ${llvm_libs})
target_include_directories(parser PRIVATE ${ANTLR_LLOPGrammar_OUTPUT_DIR})