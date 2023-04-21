//
// Created by Xinrun Miao on 4/2/23.
//

#ifndef LLVM_OOP_NOTEXPR_H
#define LLVM_OOP_NOTEXPR_H

#endif //LLVM_OOP_NOTEXPR_H


class NotExpr : public Expr {
private:
    Expr *expr;
public:
    explicit NotExpr(Expr *expr) : expr(expr) {}

    Expr *Expr() { return expr; }

    GenValue *codegen(Context* ctx) override;
};