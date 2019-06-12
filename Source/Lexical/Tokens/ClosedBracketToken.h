//
// Created by a_mod on 09.01.2019.
//
#pragma once
#include <Lexical/IToken.h>

namespace ACC{
    struct ClosedBracketToken : public IToken{
        explicit ClosedBracketToken() : IToken() {id = Symbol::CLOSED_BRACKET;};

        std::string getIdentifier() override{
            return "Closed Bracket";
        }

        friend inline bool operator==(ClosedBracketToken const & lhs, ClosedBracketToken const & rhs){
            return true;
        }
    };
}