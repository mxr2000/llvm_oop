//
// Created by Xinrun Miao on 4/25/23.
//

#include "llop/AST/AST.h"

ValueType* ValueType::IntType = new ValueType(BasicType::Int);
ValueType* ValueType::BoolType = new ValueType(BasicType::Bool);
ValueType* ValueType::LongType = new ValueType(BasicType::Long);
ValueType* ValueType::CharType = new ValueType(BasicType::Char);
