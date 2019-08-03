//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ArrowToken : public IToken{
        explicit ArrowToken(size_t lineNum) : IToken(Symbol::ARROW, lineNum) {};

        std::string getIdentifier() override{
            return "->";
        }

        friend inline bool operator==(const ArrowToken&, const ArrowToken&){
            return true;
        }
    };
}