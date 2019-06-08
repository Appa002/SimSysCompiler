//
// Created by a_mod on 03.06.2019.
//
#pragma once
#include <Structure/Structure.h>
#include "Structure/Structures/ElementaryStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"

namespace ACC{
    class BoolLValueStructure : public GenericLValueStructure{
    public:
        explicit BoolLValueStructure(std::string const & access);
    };
}
