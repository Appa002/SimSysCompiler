//
// Created by a_mod on 02.03.2019.
//

#ifndef SIMSYSCOMPILER_ASSEMBLY_H
#define SIMSYSCOMPILER_ASSEMBLY_H

#include <string>
#include <IntermediateCodeGenerator/IntermediateCode.h>

namespace ACC {
    class Assembly {
    private:
        std::string dataSection;
        std::string textSection;

        size_t textSectionPos = 0;
        size_t dataSectionPos = 0;

    public:
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


    };
}

#endif //SIMSYSCOMPILER_ASSEMBLY_H
