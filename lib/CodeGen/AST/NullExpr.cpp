//
// Created by Xinrun Miao on 4/25/23.
//

#include "llop/AST/AST.h"
#include "llop/CodeGen/Context.h"

GenValue *NullExpr::codegen(Context *ctx) {
    return new NullGenValue();
}