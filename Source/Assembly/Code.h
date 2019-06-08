//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_CODE_H
#define SIMSYSCOMPILER_CODE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <General/Type.h>
#include <functional>
#include <General/Stack.h>
#include <memory>
#include <General/ScopedSymbolTable.h>
#include "Fn.h"

#include <Structure/Structure.h>

namespace ACC{
    std::string registerToString(size_t size, Register reg);

    class Code {
    private:
        size_t uuidCounter = 0;

        std::unordered_map<std::string, Fn> fnTable;
        std::unordered_map<Register, bool> freeRegisterTable;

        ScopedSymbolTable<std::shared_ptr<Structure>>* curScope = nullptr;
        std::shared_ptr<ScopedSymbolTable<std::shared_ptr<Structure>>> globalScope = nullptr;

        Stack<std::string> fnStack;
        std::string dataSection;

    public:
        Code();

        void reserveRegister(Register reg);
        void freeRegister(Register reg);
        void freeRegister(std::vector<Register> regs);
        bool isRegisterFree(Register reg);
        void popFnFromStack();
        Register getFreeRegister();

        std::shared_ptr<Structure> getVarSymbol(std::string sym);
        std::shared_ptr<Structure> emplaceVarSymbol(std::string sym, std::shared_ptr<Structure> struc);

        Fn& getFnSymbol(std::string sym);
        Fn& getFnSymbol();
        Fn& emplaceFnSymbol(std::string sym);

        void writeLineToData(std::string const & str);
        std::string combineOutput();
        std::string getUUID();

        void pushScope();
        void popScope();
    };
}

#endif //SIMSYSCOMPILER_CODE_H
