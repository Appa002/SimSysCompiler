//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct DotToken : public IToken{
        explicit DotToken(size_t lineNum) : IToken(Symbol::DOT, lineNum) {};

        std::string getIdentifier() override{
            return ".";
        }

        friend inline bool operator==(const DotToken&, const DotToken&){
            return true;
        }
    };
}