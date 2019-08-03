//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct QuoteToken : public IToken{
        explicit QuoteToken(size_t lineNum) : IToken(Symbol::QUOTE, lineNum) {};

        std::string getIdentifier() override{
            return "Quote";
        }

        friend inline bool operator==(const QuoteToken&, const QuoteToken&){
            return true;
        }
    };
}