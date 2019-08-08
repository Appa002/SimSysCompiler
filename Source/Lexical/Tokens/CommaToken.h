//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct CommaToken : public IToken{
        explicit CommaToken(size_t lineNum) : IToken(Symbol::COMMA, lineNum) {};

        std::string getIdentifier() override{
            return "comma";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return ",";
        };

        friend inline bool operator==(const CommaToken&, const CommaToken&){
            return true;
        }
    };
}

