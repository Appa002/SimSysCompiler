//
// Created by a_mod on 16.03.2019.
//

#ifndef SIMSYSCOMPILER_ASSEMBLYFUNCTION_H
#define SIMSYSCOMPILER_ASSEMBLYFUNCTION_H

#include <string>
#include <AssemblyGenerator/Location.h>
#include <vector>

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
        uint32_t curBpOffset = 0;
        uint32_t requiredStackSize = 0;

    public:
        AssemblyFunction() = default;
        explicit AssemblyFunction(std::string sym);

        void writeLine(const std::string & line);

        void mov(std::string target, std::string source, std::string comment = "");
        void mov(std::string target, std::string source, SizeDefinition size, bool ptr = false,
                 std::string comment = "");

        std::string generateCode();

        void createStructure(Location where, std::string structure, std::vector<Location> data);

    };
}

#endif //SIMSYSCOMPILER_ASSEMBLYFUNCTION_H
