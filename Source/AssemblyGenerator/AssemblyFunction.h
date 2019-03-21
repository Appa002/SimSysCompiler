//
// Created by a_mod on 16.03.2019.
//

#ifndef SIMSYSCOMPILER_ASSEMBLYFUNCTION_H
#define SIMSYSCOMPILER_ASSEMBLYFUNCTION_H

#include <string>

namespace ACC {

    enum class SizeDefinition{
        dowrd,
        qword,
        word,
        byte
    };

    std::string sizeToString(SizeDefinition size);

    class AssemblyFunction {
    public:
        std::string code;
        std::string symbol;

    public:
        AssemblyFunction() = default;
        explicit AssemblyFunction(std::string sym);

        void writeLine(const std::string & line);

        void mov(std::string target, std::string source, std::string comment = "");
        void mov(std::string target, std::string source, SizeDefinition size, bool ptr = false,
                 std::string comment = "");




    };
}

#endif //SIMSYSCOMPILER_ASSEMBLYFUNCTION_H
