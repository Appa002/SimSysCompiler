//
// Created by a_mod on 16.05.2019.
//

#ifndef SIMSYSCOMPILER_FN_H
#define SIMSYSCOMPILER_FN_H

#include <string>
#include <Types/Type.h>
#include <vector>

namespace ACC {

    /*! Contains the assembly code for a function.*/
    struct Fn {
        Fn() = default;
        Fn(std::string const & sym);

        std::string code;
        std::string symbol;
        uint32_t curBpOffset = 0;

        /*! Writes one line of assembly code.
         * @param line The line to write*/
        void writeLine(std::string const & line);

        /*! Returns a string that contains the x86_64 assembly for this function.*/
        std::string generate() const;

        /*! Test whether or not this function has the same signature as a function with symbol `name`, returnType `returnType`, and
         * arguments of type `argsType`.
         * @param name The symbol of the Function being matched.
         * @param returnType The returnType of the function being matched.
         * @param argsType The type of the argument being matched.
         * @return A bool  whether or not the signature is the same. */
        bool matches(std::string name, Type returnType, std::vector<Type> argsType);

        /*! Returns a mangled name based on the Signature.*/
        std::string mangledName() const;

        /*! The return type of this function.*/
        Type returnType = Type("", 0);

        /*! The types of this functions arguments.*/
        std::vector<Type> argsType;
    };
}

#endif //SIMSYSCOMPILER_FN_H