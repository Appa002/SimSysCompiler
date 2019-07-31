//
// Created by a_mod on 02.07.2019.
//

#pragma once

#include <Assembly/Fn.h>
#include <General/builtinTypes.h>

/* Contains all overloads for the builtin function `num`.*/
namespace ACC::BuiltIns::Num{
    Fn get_char(){
        Fn fn;
        fn.returnType = Type(BuiltIns::numType);
        fn.symbol = "num";
        fn.curBpOffset = 0;
        fn.argsType = {Type(BuiltIns::charType)};
        fn.code =
                R"(
movzx rax, byte [rbp + 16]
leave
ret
)";
        return fn;
    }
}
