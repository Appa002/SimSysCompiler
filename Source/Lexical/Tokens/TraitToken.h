//
// Created by a_mod on 09.02.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct TraitToken : public IToken{
        explicit TraitToken(size_t lineNum) : IToken(Symbol::TRAIT, lineNum) {};

        std::string getIdentifier() override{
            return "Trait";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "trait";
        };

        friend inline bool operator==(TraitToken const & lhs, TraitToken const & rhs){
            return true;
        }
    };
}


