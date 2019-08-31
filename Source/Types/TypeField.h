//
// Created by a_mod on 31.08.2019.
//

#pragma once

#include <string>
#include <utility>

namespace ACC {
    struct TypeField {
        TypeField() = default;
        TypeField(std::string name, std::string typeName, bool isPtr)
                : name(std::move(name)), typeName(std::move(typeName)), isPtr(isPtr) {}

        std::string name;
        std::string typeName;
        bool isPtr = false;
    };
}

