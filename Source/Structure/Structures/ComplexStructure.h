//
// Created by a_mod on 07.06.2019.
//

#pragma once

#include <Structure/Structure.h>

#include <utility>

namespace ACC {
    class ComplexStructure : public Structure{
    public:
        explicit ComplexStructure(ValueCategory v, Type type) : Structure(v, std::move(type)) {};
    };
}

