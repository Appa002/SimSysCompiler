//
// Created by a_mod on 02.03.2019.
//

#ifndef SIMSYSCOMPILER_ASSEMBLY_H
#define SIMSYSCOMPILER_ASSEMBLY_H

#include <string>
#include <IntermediateCodeGenerator/IntermediateCode.h>
#include <AssemblyGenerator/Snippet.h>
#include "AssemblyFunction.h"
#include <Stack.h>

namespace ACC {
    class Assembly {
    private:
        std::string dataSection;
        std::string textSection;

        size_t textSectionPos = 0;
        size_t dataSectionPos = 0;

        std::unordered_map<temporary, Snippet> registerTable;
        std::unordered_map<std::string, AssemblyFunction> functionTable;

    public:
        Stack<std::string> functionStack;

        void generate(const IntermediateCode& ir);
        void print();
        void writeToFile(std::string path = "./a.asm");

        size_t writeToText(std::string text, size_t pos);
        size_t writeToText(std::string text);

        size_t writeToData(std::string text, size_t pos);
        size_t writeToData(std::string text);

        std::string combinedOutput();
        std::string getTextSection();
        std::string getDataSection();

        Snippet fetchSnippet(temporary reg);
        void emplaceSnippet(temporary reg, Snippet const & snippet);

        AssemblyFunction& fetchFunction(std::string sym);
        AssemblyFunction& fetchFunction();
        AssemblyFunction& emplaceFunction(std::string sym);


    };
}

#endif //SIMSYSCOMPILER_ASSEMBLY_H
