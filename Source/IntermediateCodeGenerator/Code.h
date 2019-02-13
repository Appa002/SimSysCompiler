//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_CODE_H
#define SIMSYSCOMPILER_CODE_H

#include <vector>
#include <string>
#include <IntermediateCodeGenerator/RepresentationTypes.h>
#include <unordered_map>

namespace ACC{
    class Code {
    private:
        std::vector<Operator> data;
        std::unordered_map<std::string, temporary> symTable;
        temporary temporaryCounter = 1;

    public:
        temporary getSymbol(std::string sym);
        temporary emplaceSymbol(std::string sym);
        void emplaceOperator(const Operator& op);
        temporary getLastTemporary();
        temporary createTemporary();
        Operator& at(size_t idx);

        std::vector<Operator>::iterator begin();
        std::vector<Operator>::iterator end();

        std::vector<Operator>& getData();

    };
}

#endif //SIMSYSCOMPILER_CODE_H
