add_library(ast)

target_sources(ast PRIVATE
        Node.cpp
        FuncHeader.cpp
        ClassDecl.cpp
        InterfaceDecl.cpp
        FuncDecl.cpp
        ValueType.cpp
        )