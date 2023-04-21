add_library(code_gen)

target_sources(code_gen PRIVATE
        CodeGen.cpp
        Context.cpp
        GenValue.cpp
        SymbolTable.cpp

        AST/Program.cpp
        AST/ClassDecl.cpp
        AST/StaticDecl.cpp
        AST/InterfaceDecl.cpp
        AST/FuncDecl.cpp


        AST/IfStmt.cpp
        AST/WhileStmt.cpp
        AST/AssignStmt.cpp
        AST/ReturnStmt.cpp
        AST/BlockStmt.cpp
        AST/VariableDeclStmt.cpp
        AST/OutputStmt.cpp

        AST/NumberExpr.cpp
        AST/VariableExpr.cpp
        AST/NewObjectExpr.cpp
        AST/TypeCoercionExpr.cpp
        AST/AndExpr.cpp
        AST/OrExpr.cpp
        AST/NotExpr.cpp
        AST/RelationalExpr.cpp
        AST/BinaryExpr.cpp
        AST/NegExpr.cpp
        AST/FuncCallExpr.cpp
        AST/AccessExpr.cpp
        AST/IsExpr.cpp
        AST/StaticAccessExpr.cpp
        AST/SuperExpr.cpp
        AST/SelfExpr.cpp
        )

llvm_map_components_to_libnames(llvm_libs Support Core Passes)
target_link_libraries(code_gen PRIVATE ${llvm_libs})