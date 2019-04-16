#pragma once

#include <string>
#include <vector>
#include <AssemblyGenerator/Location.h>

namespace ACC{
    namespace Movs{

        /*! Moves a vector of constants onto the top of the stack.*/
        std::string c2st(std::vector<Location> constants);

    }
}