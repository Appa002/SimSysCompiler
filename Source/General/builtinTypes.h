//
// Created by a_mod on 11.05.2019.
//
#pragma once

#include <General/Type.h>

namespace ACC::BuiltIns{
    const auto __none = Type(0, 0);
    const auto numType = Type(1, 8);
    const auto charType = Type(2, 1);
    const auto ptrType = Type(3, 8);
    const auto boolType = Type(4, 1);

    Type ptr(Type other){
        Type ptr = ptrType;
        ptr.pointingTo = other;
        return ptr;
    }

}