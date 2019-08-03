//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ClosedCurlyToken : public IToken{
        explicit ClosedCurlyToken(size_t lineNum) : IToken(Symbol::CLOSED_CURLY, lineNum) {};

        std::string getIdentifier() override{
            return "}";
        }

        friend inline bool operator==(const ClosedCurlyToken&, const ClosedCurlyToken&){
            return true;
        }
    };
}