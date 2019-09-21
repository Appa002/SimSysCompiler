//
// Created by a_mod on 31.08.2019.
//

#pragma once

#include <Structure/Structure.h>
#include <Structure/Structures/ComplexStructure.h>

namespace ACC {
    class UserStructure : public ComplexStructure {
    public:
        ValueCategory valueCategory;
        Type type;

        UserStructure(ValueCategory v, const Type& t);
    };
}

