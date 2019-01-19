//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_INSTRUCTION_H
#define SIMSYSCOMPILER_INSTRUCTION_H

#include <functional>

namespace ACC{
    enum class InstructionId{
        CHANGE_CONTEXT,
        NEW_TOKEN,
        NOP
    };
    class IToken;
    class IContext;

    struct Instruction{
        using context_func = std::function<IContext*(void)>;
        using token_func = std::function<IToken*(const std::string&, const std::string::iterator&, const std::string::iterator&)>;
        using nop_func = nullptr_t;

        Instruction(InstructionId  id, void* ptr) : func(ptr), id(id) {};
        Instruction() : func(nullptr), id(InstructionId::NOP) {};
        InstructionId id;
        void* func;
    };

}

#endif //SIMSYSCOMPILER_INSTRUCTION_H
