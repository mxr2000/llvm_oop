//
// Created by mbp on 2023/3/22.
//

#ifndef LLVM_OOP_AST_H
#define LLVM_OOP_AST_H


#include "Node.h"

#include "Expr/Expr.h"
#include "Expr/VariableExpr.h"
#include "Expr/BinaryExpr.h"
#include "Expr/FuncCallExpr.h"
#include "Expr/NewObjectExpr.h"
#include "Expr/NumberExpr.h"
#include "Expr/ParenExpr.h"
#include "Expr/RelationalExpr.h"
#include "Expr/UnaryExpr.h"
#include "Expr/NullExpr.h"
#include "Expr/AccessExpr.h"
#include "Expr/TypeCoercionExpr.h"

#include "Stmt/Stmt.h"
#include "Stmt/IfStmt.h"
#include "Stmt/AssignStmt.h"
#include "Stmt/ReturnStmt.h"
#include "Stmt/VariableDeclStmt.h"
#include "Stmt/WhileStmt.h"

#include "Top/ClassDecl.h"
#include "Top/FieldDecl.h"
#include "Top/FuncDecl.h"
#include "Top/InterfaceDecl.h"
#include "Top/StaticDecl.h"
#include "Top/Program.h"

#include "Fragment/FuncHeader.h"
#include "Fragment/Param.h"

#include "Type/ArrayType.h"
#include "Type/SimpleType.h"
#include "Type/Type.h"
#include "Type/ReferenceType.h"
#include "Type/ValueType.h"
#endif //LLVM_OOP_AST_H
