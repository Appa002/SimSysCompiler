//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_CODE_H
#define SIMSYSCOMPILER_CODE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <TypeId.h>
#include <functional>
#include <Stack.h>
#include <memory>
#include <ScopedSymbolTable.h>

namespace ACC{

    enum class StructureType{
        elementary,
        complex, // TODO: Reserved for later.
        NA
    };

    enum class Register;
    class Code;

    struct Structure{
        Structure() = default;
        explicit Structure(StructureType type) : type(type) {};

        std::function<std::string (Code&)> copyToStack;
        std::function<std::string (std::string, Code&)> copyToRegister;
        std::function<std::string (int32_t , Code&)> copyToBpOffset;

        StructureType type = StructureType::NA;
        std::vector<Register> registerUsed;
        TypeId typeId = TypeId(0, 0);
        bool isStored = true;
    };
    struct Fn{
        std::string code;
        std::string symbol;
        uint32_t curBpOffset = 0;
        uint32_t extraRspAddition = 0;

        void writeLine(std::string const & line);
        std::string generate();
        TypeId returnType = TypeId(0, 0);
    };

    enum class Register{
        rA,
        rB,
        rC,
        rD,
        rSI,
        rDI,
        r8,
        r9,
        r10,
        r11,
        r12,
        r13,
        r14,
        r15,
    };

    std::string registerToString(size_t size, Register reg);

    class Code {
    private:
        std::unordered_map<std::string, Fn> fnTable;
        std::unordered_map<Register, bool> freeRegisterTable;

        ScopedSymbolTable<Structure>* curScope = nullptr;
        std::shared_ptr<ScopedSymbolTable<Structure>> globalScope = nullptr;

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

        Structure& getVarSymbol(std::string sym);
        Structure& emplaceVarSymbol(std::string sym, const Structure &struc);

        Fn& getFnSymbol(std::string sym);
        Fn& getFnSymbol();
        Fn& emplaceFnSymbol(std::string sym);

        void writeLineToData(std::string const & str);
        std::string combineOutput();

        void pushScope();
        void popScope();
    };
}

#endif //SIMSYSCOMPILER_CODE_H
