//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct IndentToken : public IToken{
        explicit IndentToken(size_t lineNum) : IToken(Symbol::INDENT, lineNum) {};

        std::string getIdentifier() override{
            return "indent";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "starting block";
        };


        friend inline bool operator==(const IndentToken&, const IndentToken&){
            return true;
        }
    };
}

