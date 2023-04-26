//
// Created by Xinrun Miao on 4/1/23.
//

#include "llop/Parser/ASTBuilder.h"

RelationalOp getRelationalOp(const std::string &name) {
    if (name == "==") {
        return RelationalOp::EQ;
    } else if (name == "!=") {
        return RelationalOp::NE;
    } else if (name == ">") {
        return RelationalOp::GT;
    } else if (name == "<") {
        return RelationalOp::LT;
    } else if (name == ">=") {
        return RelationalOp::GE;
    } else if (name == "<=") {
        return RelationalOp::LE;
    }
    return RelationalOp::EQ;
}

BinaryOp getBinaryOp(const std::string &name) {
    if (name == "+") {
        return BinaryOp::Plus;
    } else if (name == "-") {
        return BinaryOp::Minus;
    } else if (name == "*") {
        return BinaryOp::Multiply;
    } else if (name == "/") {
        return BinaryOp::Divide;
    }
    return BinaryOp::Divide;
}


std::any ASTBuilder::visitIfStatement(LLOPParser::IfStatementContext *ctx) {
    visit(ctx->expr());
    Expr *condition = lastExpr;
    visit(ctx->stmt(0));
    Stmt *thenStmt = lastStmt;
    Stmt *elseStmt = nullptr;
    if (ctx->stmt().size() > 1) {
        visit(ctx->stmt(1));
        elseStmt = lastStmt;
    }
    lastStmt = new IfStmt(condition, thenStmt, elseStmt);
    return nullptr;
}

std::any ASTBuilder::visitWhileStatement(LLOPParser::WhileStatementContext *ctx) {
    visit(ctx->expr());
    Expr *condition = lastExpr;
    visit(ctx->stmt());
    Stmt *stmt = lastStmt;
    lastStmt = new WhileStmt(condition, stmt);
    return nullptr;
}

std::any ASTBuilder::visitAssignStatement(LLOPParser::AssignStatementContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastStmt = new AssignStmt(lhs, rhs);
    return nullptr;
}

std::any ASTBuilder::visitReturnStatement(LLOPParser::ReturnStatementContext *ctx) {
    visit(ctx->expr());
    Expr *expr = lastExpr;
    lastStmt = new ReturnStmt(expr);
    return nullptr;
}

std::any ASTBuilder::visitBlockStatement(LLOPParser::BlockStatementContext *ctx) {
    std::vector<Stmt *> stmts;
    for (auto *p: ctx->stmt()) {
        visit(p);
        stmts.push_back(lastStmt);
    }
    lastStmt = new BlockStmt(stmts);
    return nullptr;
}

std::any ASTBuilder::visitVariableDeclStatement(LLOPParser::VariableDeclStatementContext *ctx) {
    auto name = ctx->IDENTIFIER()->getText();
    visit(ctx->type());
    lastStmt = new VariableDeclStmt(name, lastType);
    return nullptr;
}

std::any ASTBuilder::visitNumExpr(LLOPParser::NumExprContext *ctx) {
    lastExpr = new NumberExpr(std::stoi(ctx->NUMBER()->getText()));
    return nullptr;
}

std::any ASTBuilder::visitAccessExpr(LLOPParser::AccessExprContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastExpr = new AccessExpr(lhs, rhs);
    return nullptr;
}

std::any ASTBuilder::visitVarExpr(LLOPParser::VarExprContext *ctx) {
    lastExpr = new VariableExpr(ctx->IDENTIFIER()->getText());
    return nullptr;
}

std::any ASTBuilder::visitNewExpr(LLOPParser::NewExprContext *ctx) {
    visit(ctx->referenceType());
    auto *type = (ReferenceType *) lastType;
    std::vector<Expr *> arguments;
    for (auto p: ctx->argumentList()->expr()) {
        visit(p);
        arguments.push_back(lastExpr);
    }
    lastExpr = new NewObjectExpr(type, arguments);
    return nullptr;
}

std::any ASTBuilder::visitValueType(LLOPParser::ValueTypeContext *ctx) {
    if (ctx->BOOL()) {
        lastType = ValueType::BoolType;
    } else if (ctx->INT()) {
        lastType = ValueType::IntType;
    } else if (ctx->CHAR()) {
        lastType = ValueType::CharType;
    } else if (ctx->LONG()) {
        lastType = ValueType::LongType;
    } else {
        throw std::runtime_error("Unknown type");
    }
    return nullptr;
}

std::any ASTBuilder::visitReferenceType(LLOPParser::ReferenceTypeContext *ctx) {
    lastType = new ReferenceType(ctx->getText());
    return nullptr;
}

std::any ASTBuilder::visitVoidType(LLOPParser::VoidTypeContext *ctx) {
    lastType = new VoidType();
    return nullptr;
}

std::any ASTBuilder::visitTypeCoercionExpr(LLOPParser::TypeCoercionExprContext *ctx) {
    visit(ctx->referenceType());
    auto *type = (ReferenceType *) lastType;
    visit(ctx->expr());
    auto *expr = lastExpr;
    lastExpr = new TypeCoercionExpr(expr, type);
    return nullptr;
}

std::any ASTBuilder::visitAndExpr(LLOPParser::AndExprContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastExpr = new AndExpr(lhs, rhs);
    return nullptr;
}

std::any ASTBuilder::visitOrExpr(LLOPParser::OrExprContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastExpr = new OrExpr(lhs, rhs);
    return nullptr;
}

std::any ASTBuilder::visitNotExpr(LLOPParser::NotExprContext *ctx) {
    visit(ctx->expr());
    lastExpr = new NotExpr(lastExpr);
    return nullptr;
}

std::any ASTBuilder::visitRelationalExpr(LLOPParser::RelationalExprContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastExpr = new RelationalExpr(lhs, rhs, getRelationalOp(ctx->op->getText()));
    return nullptr;
}

std::any ASTBuilder::visitAdditiveExpr(LLOPParser::AdditiveExprContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastExpr = new BinaryExpr(lhs, rhs, getBinaryOp(ctx->op->getText()));
    return nullptr;
}

std::any ASTBuilder::visitMultiplicativeExpr(LLOPParser::MultiplicativeExprContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastExpr = new BinaryExpr(lhs, rhs, getBinaryOp(ctx->op->getText()));
    return nullptr;
}

std::any ASTBuilder::visitNegExpr(LLOPParser::NegExprContext *ctx) {
    visit(ctx->expr());
    lastExpr = new NegExpr(lastExpr);
    return nullptr;
}

std::any ASTBuilder::visitFunCallExpr(LLOPParser::FunCallExprContext *ctx) {
    auto name = ctx->IDENTIFIER()->getText();
    std::vector<Expr *> arguments;
    for (auto p: ctx->argumentList()->expr()) {
        visit(p);
        arguments.push_back(lastExpr);
    }
    lastExpr = new FuncCallExpr(name, arguments);
    return nullptr;
}

std::any ASTBuilder::visitFieldDecl(LLOPParser::FieldDeclContext *ctx) {
    auto name = ctx->IDENTIFIER()->getText();
    visit(ctx->type());
    auto type = lastType;
    return new FieldDecl(name, type);
}

std::any ASTBuilder::visitClassDecl(LLOPParser::ClassDeclContext *ctx) {
    auto name = ctx->IDENTIFIER(0)->getText();
    std::cout << "Building class " << name << std::endl;
    auto parentClassName = ctx->IDENTIFIER(1)->getText();
    extendsMap.insert(std::make_pair(name, parentClassName));
    beExtendedMap[parentClassName].push_back(name);

    for (int i = 2; i < ctx->IDENTIFIER().size(); i++) {
        auto interfaceName = ctx->IDENTIFIER(i)->getText();
        implementsMap[name].push_back(interfaceName);
        beImplementedMap[interfaceName].push_back(name);
    }
    for (auto iter: ctx->fieldDecl()) {
        auto field = std::any_cast<FieldDecl *>(visit(iter));
        classFields[name].push_back(field);
    }
    for (auto iter: ctx->funcDecl()) {
        auto func = std::any_cast<FuncDecl *>(visit(iter));
        classMethods[name].push_back(func);
    }
    return nullptr;
}

std::any ASTBuilder::visitStaticDecl(LLOPParser::StaticDeclContext *ctx) {
    auto name = ctx->IDENTIFIER()->getText();
    std::cout << "Building static " << name << std::endl;
    std::vector<FuncDecl *> methods;
    for (auto f: ctx->funcDecl()) {
        methods.push_back(std::any_cast<FuncDecl *>(visit(f)));
    }
    auto decl = new StaticDecl(name, methods);
    statics.insert(std::make_pair(name, decl));
    return decl;
}

std::any ASTBuilder::visitInterfaceDecl(LLOPParser::InterfaceDeclContext *ctx) {
    auto name = ctx->IDENTIFIER()->getText();
    std::cout << "Building interface " << name << std::endl;
    std::vector<FuncHeader *> methods;
    for (auto f: ctx->funcHeader()) {
        methods.push_back(std::any_cast<FuncHeader *>(visit(f)));
        //std::cout << "Interface " << name << " " << f->IDENTIFIER()->getText() << std::endl;
    }
    auto decl = new InterfaceDecl(name, methods, std::vector<InterfaceDecl *>());
    interfaces.insert(std::make_pair(name, decl));
    return decl;
}

std::any ASTBuilder::visitFuncHeader(LLOPParser::FuncHeaderContext *ctx) {
    auto name = ctx->IDENTIFIER()->getText();
    std::vector<Param *> params;
    for (auto p: ctx->paramList()->param()) {
        params.push_back(std::any_cast<Param *>(visit(p)));
    }
    auto returnType = visit(ctx->type());
    return new FuncHeader(name, params, lastType);
}

std::any ASTBuilder::visitParam(LLOPParser::ParamContext *ctx) {
    auto name = ctx->IDENTIFIER()->getText();
    visit(ctx->type());
    return new Param(name, lastType);
}

void ASTBuilder::buildClass(ClassDecl *parent, const std::string &name) {
    auto methods = classMethods[name];
    auto fields = classFields[name];
    std::vector<InterfaceDecl *> implementedInterfaces;
    for (const auto &intName: implementsMap[name]) {
        implementedInterfaces.push_back(interfaces[intName]);
    }
    auto *decl = new ClassDecl(name, parent, implementedInterfaces, fields, methods);
    classes.insert(std::make_pair(name, decl));
    for (const auto &childName: beExtendedMap[name]) {
        buildClass(decl, childName);
    }
}

std::any ASTBuilder::visitProgram(LLOPParser::ProgramContext *ctx) {
    try {
        for (auto p: ctx->interfaceDecl()) {
            visit(p);
        }
        for (auto p: ctx->staticDecl()) {
            visit(p);
        }
        for (auto p: ctx->classDecl()) {
            visit(p);
        }
        buildClass(nullptr, "Object");
        auto *program = new Program(classes, interfaces, statics);
        return program;
    } catch (std::bad_any_cast const &err) {
        std::cout << err.what();
    }
    return nullptr;
}

ASTBuilder::ASTBuilder(LLOPParser::ProgramContext *ctx) {
    programCtx = ctx;
}

Program *ASTBuilder::build() {
    return std::any_cast<Program *>(visit(programCtx));
}

std::any ASTBuilder::visitNullExpr(LLOPParser::NullExprContext *ctx) {
    lastExpr = new NullExpr();
    return nullptr;
}

std::any ASTBuilder::visitParenExpr(LLOPParser::ParenExprContext *ctx) {
    return visit(ctx->expr());
}

std::any ASTBuilder::visitIsExpr(LLOPParser::IsExprContext *ctx) {
    visit(ctx->expr());
    Expr *expr = lastExpr;
    visit(ctx->referenceType());
    auto *type = (ReferenceType *) lastType;
    lastExpr = new IsExpr(expr, type);
    return nullptr;
}

std::any ASTBuilder::visitSelfExpr(LLOPParser::SelfExprContext *ctx) {
    lastExpr = new SelfExpr();
    return nullptr;
}

std::any ASTBuilder::visitSuperExpr(LLOPParser::SuperExprContext *ctx) {
    lastExpr = new SuperExpr();
    return nullptr;
}

std::any ASTBuilder::visitStaticAccessExpr(LLOPParser::StaticAccessExprContext *ctx) {
    visit(ctx->referenceType());
    auto *type = (ReferenceType *) lastType;
    visit(ctx->expr());
    Expr *expr = lastExpr;
    lastExpr = new StaticAccessExpr(expr, type);
    return nullptr;
}

std::any ASTBuilder::visitFuncDecl(LLOPParser::FuncDeclContext *ctx) {
    auto header = std::any_cast<FuncHeader *>(visit(ctx->funcHeader()));
    if (header->Name() == "init" && header->Params().size() == 3) {
        std::cout << "here";
    }
    visit(ctx->blockStatement());
    auto *body = (BlockStmt *) lastStmt;
    return new FuncDecl(header, body);
}

std::any ASTBuilder::visitStmt(LLOPParser::StmtContext *ctx) {
    if (ctx->expr() != nullptr) {
        visit(ctx->expr());
        lastStmt = lastExpr;
        return nullptr;
    }
    return LLOPBaseVisitor::visitStmt(ctx);
}


std::any ASTBuilder::visitOutputStatement(LLOPParser::OutputStatementContext *ctx) {
    visit(ctx->expr());
    lastStmt = new OutputStmt(lastExpr);
    return nullptr;
}

std::any ASTBuilder::visitBoolLiteralExpr(LLOPParser::BoolLiteralExprContext *ctx) {
    return nullptr;
}

std::any ASTBuilder::visitArrayType(LLOPParser::ArrayTypeContext *ctx) {
    visit(ctx->type());
    lastType = new ArrayType(lastType);
    return nullptr;
}

std::any ASTBuilder::visitArrayIndexExpr(LLOPParser::ArrayIndexExprContext *ctx) {
    visit(ctx->expr(0));
    Expr *lhs = lastExpr;
    visit(ctx->expr(1));
    Expr *rhs = lastExpr;
    lastExpr = new ArrayIndexExpr(lhs, rhs);
    return nullptr;
}

std::any ASTBuilder::visitNewArrayExpr(LLOPParser::NewArrayExprContext *ctx) {
    visit(ctx->arrayType());
    auto arrayType = dynamic_cast<ArrayType*>(lastType);
    visit(ctx->expr());
    lastExpr = new NewArrayExpr(arrayType, lastExpr);
    return nullptr;
}
