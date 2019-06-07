//
// Created by a_mod on 11.05.2019.
//
#pragma once

#include <General/TypeId.h>

namespace ACC::BuiltIns{
    const auto __none = TypeId(0, 0);
    const auto numType = TypeId(1, 8);
    const auto charType = TypeId(2, 1);
    const auto ptrNumType = TypeId(3, 8);
    const auto ptrCharType = TypeId(4, 8);
    const auto boolType = TypeId(5, 1);
}