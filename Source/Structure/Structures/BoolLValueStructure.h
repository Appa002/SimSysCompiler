//
// Created by a_mod on 03.06.2019.
//
#pragma once
#include <Structure/Structure.h>
#include "ElementaryStructure.h"
#include "ElementaryLValueStructure.h"

namespace ACC{
    class BoolLValueStructure : public ElementaryLValueStructure{
    public:
        explicit BoolLValueStructure(std::string const & access);
    };
}
