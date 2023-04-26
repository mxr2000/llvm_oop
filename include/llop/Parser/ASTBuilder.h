//
// Created by Xinrun Miao on 4/1/23.
//

#ifndef LLVM_OOP_ASTBUILDER_H
#define LLVM_OOP_ASTBUILDER_H


#include <string>
#include "LLOPParser.h"
#include "LLOPBaseVisitor.h"
#include "../AST/AST.h"


class ASTBuilder : public LLOPBaseVisitor {
private:
    LLOPParser::ProgramContext *programCtx;

    std::unordered_map<std::string, std::string> extendsMap;
    std::unordered_map<std::string, std::vector<std::string>> beExtendedMap;
    std::unordered_map<std::string, std::vector<std::string>> implementsMap;
    std::unordered_map<std::string, std::vector<std::string>> beImplementedMap;

    std::unordered_map<std::string, std::vector<FuncDecl *>> classMethods;
    //std::unordered_map<std::string, std::vector<FuncDecl *>> staticMethods;
    std::unordered_map<std::string, std::vector<FieldDecl *>> classFields;

    std::unordered_map<std::string, InterfaceDecl *> interfaces;
    std::unordered_map<std::string, ClassDecl *> classes;
    std::unordered_map<std::string, StaticDecl *> statics;

    void buildClass(ClassDecl *parent, const std::string &name);

    Expr *lastExpr = nullptr;
    Stmt *lastStmt = nullptr;
    Type *lastType = nullptr;

public:
    Program *build();

    explicit ASTBuilder(LLOPParser::ProgramContext *ctx);

    std::any visitProgram(LLOPParser::ProgramContext *ctx) override;

    /* Top level declarations */
    std::any visitClassDecl(LLOPParser::ClassDeclContext *ctx) override;

    std::any visitStaticDecl(LLOPParser::StaticDeclContext *ctx) override;

    std::any visitInterfaceDecl(LLOPParser::InterfaceDeclContext *ctx) override;

    std::any visitFuncHeader(LLOPParser::FuncHeaderContext *ctx) override;

    std::any visitParam(LLOPParser::ParamContext *ctx) override;

    std::any visitFieldDecl(LLOPParser::FieldDeclContext *ctx) override;

    std::any visitFuncDecl(LLOPParser::FuncDeclContext *ctx) override;


    /* Statements */
    std::any visitBlockStatement(LLOPParser::BlockStatementContext *ctx) override;

    std::any visitAssignStatement(LLOPParser::AssignStatementContext *ctx) override;

    std::any visitIfStatement(LLOPParser::IfStatementContext *ctx) override;

    std::any visitWhileStatement(LLOPParser::WhileStatementContext *ctx) override;

    std::any visitReturnStatement(LLOPParser::ReturnStatementContext *ctx) override;

    std::any visitVariableDeclStatement(LLOPParser::VariableDeclStatementContext *ctx) override;

    /* Expressions */
    std::any visitAccessExpr(LLOPParser::AccessExprContext *ctx) override;

    std::any visitFunCallExpr(LLOPParser::FunCallExprContext *ctx) override;

    std::any visitNumExpr(LLOPParser::NumExprContext *ctx) override;

    std::any visitVarExpr(LLOPParser::VarExprContext *ctx) override;

    std::any visitNewExpr(LLOPParser::NewExprContext *ctx) override;

    std::any visitTypeCoercionExpr(LLOPParser::TypeCoercionExprContext *ctx) override;

    std::any visitAdditiveExpr(LLOPParser::AdditiveExprContext *ctx) override;

    std::any visitMultiplicativeExpr(LLOPParser::MultiplicativeExprContext *ctx) override;

    std::any visitRelationalExpr(LLOPParser::RelationalExprContext *ctx) override;

    std::any visitAndExpr(LLOPParser::AndExprContext *ctx) override;

    std::any visitNewArrayExpr(LLOPParser::NewArrayExprContext *ctx) override;

    std::any visitOrExpr(LLOPParser::OrExprContext *ctx) override;

    std::any visitNotExpr(LLOPParser::NotExprContext *ctx) override;

    std::any visitNegExpr(LLOPParser::NegExprContext *ctx) override;

    std::any visitNullExpr(LLOPParser::NullExprContext *ctx) override;

    std::any visitParenExpr(LLOPParser::ParenExprContext *ctx) override;

    std::any visitIsExpr(LLOPParser::IsExprContext *ctx) override;

    std::any visitStaticAccessExpr(LLOPParser::StaticAccessExprContext *ctx) override;

    std::any visitSelfExpr(LLOPParser::SelfExprContext *ctx) override;

    std::any visitSuperExpr(LLOPParser::SuperExprContext *ctx) override;

    std::any visitStmt(LLOPParser::StmtContext *ctx) override;

    std::any visitArrayIndexExpr(LLOPParser::ArrayIndexExprContext *ctx) override;

    std::any visitOutputStatement(LLOPParser::OutputStatementContext *ctx) override;

    std::any visitBoolLiteralExpr(LLOPParser::BoolLiteralExprContext *ctx) override;
    /* Type */
    std::any visitValueType(LLOPParser::ValueTypeContext *ctx) override;

    std::any visitReferenceType(LLOPParser::ReferenceTypeContext *ctx) override;

    std::any visitVoidType(LLOPParser::VoidTypeContext *ctx) override;

    std::any visitArrayType(LLOPParser::ArrayTypeContext *ctx) override;

};

#endif //LLVM_OOP_ASTBUILDER_H