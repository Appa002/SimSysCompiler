#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ExitToken : public IToken{
        explicit ExitToken(size_t lineNum) : IToken(Symbol::EXIT, lineNum) {}

        std::string getIdentifier() override{
            return "Exit";
        }

        friend inline bool operator==(ExitToken const & lhs, ExitToken const & rhs){
            return true;
        }
    };
}

