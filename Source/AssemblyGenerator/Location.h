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
#include <GeneralDataStore.h>

namespace ACC {
    enum class AccessMethod{
        REGISTER,
        STACK_TOP,
        STACK_OFFSET,
        SBP_OFFSET,
        HEAP,
        IMMEDIAT,
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

        template <class T>
        static Location immediat(T c){
            auto l = Location(AccessMethod::IMMEDIAT);
            l.immediatInfo.storeT<T>(c);
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
        GeneralDataStore immediatInfo;
    };
}

#endif //SIMSYSCOMPILER_SNIPPET_H
