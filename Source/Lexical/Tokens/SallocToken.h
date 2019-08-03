#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct SallocToken : public IToken{

        explicit SallocToken(size_t lineNum) : IToken(Symbol::SALLOC, lineNum) {}

        std::string getIdentifier() override{
            return "salloc";
        }

        friend inline bool operator==(SallocToken const & lhs, SallocToken const & rhs){
            return true;
        }
    };
}

