#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct MinusToken : public IToken{
        MinusToken(size_t lineNum) : IToken(Symbol::MINUS, lineNum) {}

        std::string getIdentifier() override{
            return "Minus";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "-";
        };

        friend inline bool operator==(MinusToken const & lhs, MinusToken const & rhs){
            return true;
        }
    };
}

