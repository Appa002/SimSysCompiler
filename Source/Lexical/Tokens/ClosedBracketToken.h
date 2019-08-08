//
// Created by a_mod on 09.01.2019.
//
#pragma once
#include <Lexical/IToken.h>

namespace ACC{
    struct ClosedBracketToken : public IToken{
        explicit ClosedBracketToken(size_t lineNum) : IToken(Symbol::CLOSED_BRACKET, lineNum) {};

        std::string getIdentifier() override{
            return "Closed Bracket";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return ")";
        };

        friend inline bool operator==(ClosedBracketToken const & lhs, ClosedBracketToken const & rhs){
            return true;
        }
    };
}