//
// Created by a_mod on 16.05.2019.
//

#ifndef SIMSYSCOMPILER_FN_H
#define SIMSYSCOMPILER_FN_H

#include <string>
#include <General/TypeId.h>

namespace ACC {

    struct Fn {
        std::string code;
        std::string symbol;
        uint32_t curBpOffset = 0;

        void writeLine(std::string const & line);
        std::string generate();
        TypeId returnType = TypeId(0, 0);
    };
}

#endif //SIMSYSCOMPILER_FN_H
