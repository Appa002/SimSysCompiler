//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct DoubleQuoteToken : public IToken{
        explicit DoubleQuoteToken(size_t lineNum) : IToken(Symbol::DOUBLE_QUOTE, lineNum) {};

        std::string getIdentifier() override{
            return "Double Quote";
        }

        friend inline bool operator==(const DoubleQuoteToken&, const DoubleQuoteToken&){
            return true;
        }
    };
}