#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct NotToken : public IToken{
        explicit NotToken(size_t lineNum) : IToken(Symbol::NOT, lineNum) {}
        std::string getIdentifier() override{
            return "Not";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "!";
        };

        friend inline bool operator==(NotToken const & lhs, NotToken const & rhs){
            return true;
        }
    };
}

