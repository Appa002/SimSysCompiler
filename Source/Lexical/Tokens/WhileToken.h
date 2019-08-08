#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct WhileToken : public IToken{

        explicit WhileToken(size_t lineNum) : IToken(Symbol::WHILE, lineNum) {}

        std::string getIdentifier() override{
            return "While";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "while";
        };

        friend inline bool operator==(WhileToken const & lhs, WhileToken const & rhs){
            return true;
        }
    };
}

