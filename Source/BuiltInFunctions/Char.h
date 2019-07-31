//
// Created by a_mod on 02.07.2019.
//

#pragma once

#include <Assembly/Fn.h>
#include <General/builtinTypes.h>

/* Contains all overloads for the builtin function `char`.*/
namespace ACC::BuiltIns::Char{
    Fn get_num(){
        Fn fn;
        fn.returnType = Type(BuiltIns::charType);
        fn.symbol = "char";
        fn.curBpOffset = 0;
        fn.argsType = {Type(BuiltIns::numType)};
        fn.code =
R"(
mov al, [rbp + 16]
leave
ret
)";

        return fn;
    }
}
