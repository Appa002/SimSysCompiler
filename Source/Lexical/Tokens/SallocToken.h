#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct Salloc : public IToken{
        Salloc() : IToken() {this->id = Symbol::SALLOC;}
        std::string getIdentifier() override{
            return "salloc";
        }

        friend inline bool operator==(Salloc const & lhs, Salloc const & rhs){
            return true;
        }
    };
}

