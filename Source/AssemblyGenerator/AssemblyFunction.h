//
// Created by a_mod on 16.03.2019.
//

#ifndef SIMSYSCOMPILER_ASSEMBLYFUNCTION_H
#define SIMSYSCOMPILER_ASSEMBLYFUNCTION_H

#include <string>

namespace ACC {
    class AssemblyFunction {
    public:
        std::string code;
        std::string symbol;

    public:
        AssemblyFunction() = default;
        explicit AssemblyFunction(std::string sym);

        void writeLine(const std::string & line);

    };
}

#endif //SIMSYSCOMPILER_ASSEMBLYFUNCTION_H
