#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct StarToken : public IToken{

        explicit StarToken(size_t lineNum) : IToken(Symbol::STAR, lineNum) {}

        std::string getIdentifier() override{
            return "Star(*)";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "*";
        };

        friend inline bool operator==(StarToken const & lhs, StarToken const & rhs){
            return true;
        }
    };
}

