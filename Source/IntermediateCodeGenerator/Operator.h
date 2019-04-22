//
// Created by a_mod on 10.02.2019.
//

#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include <Logger/Logger.h>

namespace ACC{
    using address = uint32_t;
    using temporary = uint32_t;

    enum class OperatorId{
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        COPY,
        PRINT,
        EXIT,
        FUNCTION,
        LATTR,
        SATTR,
        RETURN,

        imm_start,

        IADD,
        ISUBTRACT,
        IMULTIPLY,
        IDIVIDE,
        ICOPY,
        IPRINT,
        IEXIT,
        ICALL,
        ISATTR,
        IRETURN
    };

    bool isImmediat(OperatorId opid);

    struct Operator{
    private:
        bool dead = false;

    public:
        Operator(OperatorId id, address lhs, address rhs, temporary result);
        OperatorId id;
        address lhs;
        address rhs;
        temporary result;

        Operator* opLhs = nullptr;
        Operator* opRhs = nullptr;

        void printDependency(std::string indent, bool isLast) const;
        std::string asString() const;
        void makeDead();
        bool isDead();
    };


}