#pragma once

#include <string>
#include <vector>
#include <Stack.h>
#include <AssemblyGenerator/Location.h>

namespace ACC {
    namespace Movs {

        /*! Creates a string which contains x86_64 assembler to have constants (given as vector \p constants) on top of
         * the stack.*/
        std::string c2st(Location value);

        /*! Creates a string which contains x86_64 assembler to copy data stored at an offset from the base pointer on top
         * op the stack.*/
        std::string bp2st(Location where, Stack<size_t> &structure);

        /*! Creates a string which contains x86_64 assembler to have constants (given as vector \p constants) at some
         * offset from the base pointer.*/
        std::string c2bp(Location constant, Location where);

        std::string r2bp(Location where, Location reg);

        std::string c2so(Location constant, Location where);

        std::string r2st(Location reg);
    }
}