#pragma once

#include <string>
#include <vector>
#include <Stack.h>
#include <AssemblyGenerator/Location.h>

namespace ACC {
    namespace Movs {

        /*! Creates a string which contains x86_64 assembler to have a immediate (given as Location \p immediat) on top of
         * the stack.*/
        std::string imm2st(Location immediat);

        /*! Creates a string which contains x86_64 assembler to copy data stored at an offset from the base pointer on top
         * op the stack.*/
        std::string bp2st(Location where, Stack<size_t> &structure);

        /*! Creates a string which contains x86_64 assembler to have immediat (given as Location \p immediat) at some
         * offset from the base pointer.*/
        std::string imm2bp(Location immediat, Location where);

        std::string r2bp(Location where, Location reg);

        std::string imm2so(Location immediat, Location where);

        std::string r2st(Location reg);

        std::string bp2r(Location where, Location reg);
    }
}