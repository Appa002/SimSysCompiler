//
// Created by a_mod on 09.01.2019.
//
#pragma once
#include <Lexical/IToken.h>

namespace ACC{

    struct OpenBracketToken : public IToken{
        explicit OpenBracketToken(size_t lineNum) : IToken(Symbol::OPEN_BRACKET, lineNum) {};

        std::string getIdentifier() override{
                return "Open Bracket";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "(";
        };

        friend inline bool operator==(OpenBracketToken const & lhs, OpenBracketToken const & rhs){
            return true;
        }
    };
}