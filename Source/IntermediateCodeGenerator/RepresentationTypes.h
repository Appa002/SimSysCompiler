//
// Created by a_mod on 10.02.2019.
//

#pragma once

#include <stdint.h>
#include <vector>

namespace ACC{
    using address = uint32_t;
    using temporary = uint32_t;

    enum class OperatorId{
        PLUS,
        MINUS,
        COPY,
        ICOPY,
        PRINT
    };

    struct Operator{
        Operator(OperatorId id, address lhs, address rhs, temporary result) :  id(id), lhs(lhs), rhs(rhs), result(result) {};
        OperatorId id;
        address lhs;
        address rhs;
        temporary result;
    };


}