#include <utility>

#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>
#include <Types/Type.h>

namespace ACC{
    struct ForToken : public IToken{
        explicit ForToken(size_t lineNum) : IToken(Symbol::FOR, lineNum) {}

        std::string getIdentifier() override{
            return "for";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "for";
        };

        friend inline bool operator==(ForToken const & lhs, ForToken const & rhs){
            return true;
        }
    };
}

