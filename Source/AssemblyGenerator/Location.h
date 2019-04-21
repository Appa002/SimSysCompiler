#include <utility>

//
// Created by a_mod on 02.03.2019.
//



#ifndef SIMSYSCOMPILER_SNIPPET_H
#define SIMSYSCOMPILER_SNIPPET_H

#include <string>
#include <variant>
#include <utility>
#include <stdexcept>

namespace ACC {
    enum class AccessMethod{
        REGISTER,
        STACK_TOP,
        STACK_OFFSET,
        SBP_OFFSET,
        HEAP,
        CONSTANT,
        NONE
    };

    enum class Register{
        rax,
        rbx,
        rcx,
        rdx,
        rbp,
        rsi,
        rdi,
        rsp,
        r8,
        r9,
        r10,
        r11,
        r12,
        r13,
        r14,
        r15,
        NONE
    };

    using ptr_t = uint64_t;
    using offset_t = signed long;
    struct Location{
    private:
        explicit Location(AccessMethod accessMethod) : accessMethod(accessMethod) {};

    public:
        Location() = default;
        static Location reg(Register regInfo){
            auto l = Location(AccessMethod::REGISTER);
            l.regInfo = regInfo;
            return l;
        }

        static Location stackTop(){
            return Location(AccessMethod::STACK_TOP);
        }

        static Location constant(std::string const & str){
            auto l = Location(AccessMethod::CONSTANT);
            l.constantInfo = str;
            return l;
        }

        static Location constant(unsigned char c){
            auto l = Location(AccessMethod::CONSTANT);
            l.constantInfo = c;
            return l;
        }

        static Location stackOffset(offset_t offset){
            auto l = Location(AccessMethod::STACK_OFFSET);
            l.offsetInfo = offset;
            return l;
        }

        static Location baseOffset(offset_t offset){
            auto l = Location(AccessMethod::SBP_OFFSET);
            l.offsetInfo = offset;
            return l;
        }

        static Location heap(ptr_t ptr){
            auto l = Location(AccessMethod::HEAP);
            l.heapInfo = ptr;
            return l;
        }

        static Location none(){
            return Location(AccessMethod::NONE);
        }


        AccessMethod accessMethod = AccessMethod::NONE;
        Register regInfo = Register::NONE;
        offset_t offsetInfo = 0;
        ptr_t heapInfo = 0;
        std::string constantInfo;
    };
}

#endif //SIMSYSCOMPILER_SNIPPET_H
