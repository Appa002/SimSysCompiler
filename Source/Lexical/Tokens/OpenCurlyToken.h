//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct OpenCurlyToken : public IToken{
        explicit OpenCurlyToken(size_t lineNum) : IToken(Symbol::OPEN_CURLY, lineNum) {};

        std::string getIdentifier() override{
            return "{";
        }

        friend inline bool operator==(const OpenCurlyToken&, const OpenCurlyToken&){
            return true;
        }
    };
}