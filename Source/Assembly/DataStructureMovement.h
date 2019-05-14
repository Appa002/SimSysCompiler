#pragma once

#include <string>
#include <vector>
#include <Stack.h>
#include <GeneralDataStore.h>

using offset_t = int32_t;

namespace ACC {
    namespace Movs {

        /*! Creates a string which contains x86_64 assembler to have a immediate (given as Location \p immediat) on top of
         * the stack.*/
        std::string imm2st(const GeneralDataStore &immediat);

        /*! Creates a string which contains x86_64 assembler to copy data stored at an offset from the base pointer on top
         * op the stack.*/
        std::string bp2st(offset_t offset, size_t count);

        /*! Creates a string which contains x86_64 assembler to have immediat (given as Location \p immediat) at some
         * offset from the base pointer.*/
        std::string imm2bp(GeneralDataStore immediat, offset_t offset);

        std::string r2bp(offset_t offset, std::string reg);

        std::string imm2so(GeneralDataStore immediat, offset_t offset);

        std::string r2st(std::string reg);

        std::string bp2r(offset_t offset, std::string reg);

        std::string bp2bp(offset_t offseta, offset_t offsetb, std::string reg, size_t size);

    }
}