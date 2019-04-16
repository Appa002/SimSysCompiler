//
// Created by a_mod on 02.03.2019.
//

#ifndef SIMSYSCOMPILER_ASSEMBLY_H
#define SIMSYSCOMPILER_ASSEMBLY_H

#include <string>
#include <IntermediateCodeGenerator/IntermediateCode.h>
#include <AssemblyGenerator/Location.h>
#include "AssemblyFunction.h"
#include <Stack.h>

namespace ACC {
    class Assembly {
    private:
        std::string dataSection;
        std::string textSection;

        size_t textSectionPos = 0;
        size_t dataSectionPos = 0;


        std::unordered_map<temporary, Location> registerTable;
        std::unordered_map<std::string, AssemblyFunction> functionTable;

    public:
        Stack<std::string> functionStack;

        void generate(const IntermediateCode& ir);
        void print();
        void writeToFile(std::string path = "./a.asm");

        size_t writeToText(std::string text, size_t pos);
        size_t writeToText(std::string text);
        std::string getTextSection();

        size_t writeToData(std::string text, size_t pos);
        size_t writeToData(std::string text);
        std::string getDataSection();

        std::string combinedOutput();

        Location fetchLocation(temporary reg);
        void emplaceLocation(temporary reg, Location const &snippet);

        AssemblyFunction& fetchFunction(std::string sym);
        AssemblyFunction& fetchFunction();
        AssemblyFunction& emplaceFunction(std::string sym);

        void createStructure(Location where, std::string structure, std::vector<Location> data);


    };
}

#endif //SIMSYSCOMPILER_ASSEMBLY_H
