#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct PlusToken : public IToken{
        explicit PlusToken(size_t lineNum) : IToken(Symbol::PLUS, lineNum) {}

        std::string getIdentifier() override{
            return "Plus";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "+";
        };

        friend inline bool operator==(PlusToken const & lhs, PlusToken const & rhs){
            return true;
        }
    };
}

