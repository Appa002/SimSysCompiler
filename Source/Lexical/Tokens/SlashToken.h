#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct SlashToken : public IToken{
        explicit SlashToken(size_t lineNum) : IToken(Symbol::SLASH, lineNum) {}

        std::string getIdentifier() override{
            return "Slash(/)";
        }

        friend inline bool operator==(SlashToken const & lhs, SlashToken const & rhs){
            return true;
        }
    };
}

