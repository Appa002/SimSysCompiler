//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct OrToken : public IToken{
        explicit OrToken(size_t lineNum) : IToken(Symbol::OR, lineNum) {};

        std::string getIdentifier() override{
            return "||";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "||";
        };

        friend inline bool operator==(const OrToken&, const OrToken&){
            return true;
        }
    };
}