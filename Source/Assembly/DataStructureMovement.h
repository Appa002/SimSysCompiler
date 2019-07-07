#pragma once

#include <string>
#include <vector>
#include <General/Stack.h>
#include <General/GeneralDataStore.h>

using offset_t = int32_t;

namespace ACC {
    namespace Movs {

        /*! Creates a string which contains x86_64 assembler to have immediat (given as Location \p immediat) at some
         * offset from the base pointer.*/
        std::string imm2bp(GeneralDataStore immediat, offset_t offset);
    }
}