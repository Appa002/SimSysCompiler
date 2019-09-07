//
// Created by a_mod on 01.09.2019.
//

#pragma once


#include <Assembly/Fn.h>
#include <General/builtinTypes.h>

namespace ACC::BuiltIns::byteWiseCopy{
    Fn get(){
        // Signature:
        // ByteWiseCopy(dest : ptr<char>, src : ptr<char>, num size) -> num

        Fn fn;
        fn.returnType = Type("num", 8);
        fn.symbol = "?byteWiseCopy";
        fn.curBpOffset = 32;
        fn.argsType = {
                Type::createPtr("char"),
                Type::createPtr("char"),
                Type("num", 8)
        };


        fn.code =
                R"(
mov r15, [rbp + 16]
mov [rbp - 8], r15
mov r15, [rbp + 24]
mov [rbp - 16], r15
mov r15, [rbp + 32]
mov [rbp - 24], r15
mov qword [ rbp - 32 ], 0
.a:
mov r15, [rbp - 32]
mov r14, [rbp - 24]
cmp r15, r14
setl r15b
cmp r15b, 1
jne .b
mov r15, [rbp - 8]
mov r14, [rbp - 32]
add r15, r14
mov r14, [rbp - 16]
mov r13, [rbp - 32]
add r14, r13
mov r13, r14
mov r13b, [r13]
mov r14, r15
mov [ r14 ], r13b
mov r15, [rbp - 32]
mov r14, 1
add r15, r14
mov [ rbp - 32 ], r15
jmp .a
.b:
mov rax, 0
leave
)";
        return fn;

        /*Assembly from compiling:

fn ByteWiseCopy (dest : ptr<char>, src : ptr<char>, size : num) -> num:
    var i : num = 0;
    for i -> size:
        *(src + i) = *(dest + i);
    return 0;

         * */

    }
}
