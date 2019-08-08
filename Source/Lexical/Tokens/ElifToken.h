//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ElifToken : public IToken{
        explicit ElifToken(size_t lineNum) : IToken(Symbol::ELIF, lineNum) {};

        std::string getIdentifier() override{
            return "elif";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "elif";
        };

        friend inline bool operator==(const ElifToken&, const ElifToken&){
            return true;
        }
    };
}