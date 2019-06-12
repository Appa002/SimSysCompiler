//
// Created by a_mod on 09.01.2019.
//
#pragma once
#include <Lexical/IToken.h>

namespace ACC{

    struct OpenBracketToken : public IToken{
        explicit OpenBracketToken() : IToken() {id = Symbol::OPEN_BRACKET;};

        std::string getIdentifier() override{
                return "Open Bracket";
        }

        friend inline bool operator==(OpenBracketToken const & lhs, OpenBracketToken const & rhs){
            return true;
        }
    };
}