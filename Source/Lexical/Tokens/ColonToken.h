//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ColonToken : public IToken{
        explicit ColonToken(size_t lineNum) : IToken(Symbol::COLON, lineNum) {};

        std::string getIdentifier() override{
            return "colon";
        }

        friend inline bool operator==(const ColonToken&, const ColonToken&){
            return true;
        }
    };
}

