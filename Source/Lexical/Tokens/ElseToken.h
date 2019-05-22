//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ElseToken : public IToken{
        ElseToken() : IToken() {id = Symbol::ELSE;};

        std::string getIdentifier() override{
            return "else";
        }

        friend inline bool operator==(const ElseToken&, const ElseToken&){
            return true;
        }
    };
}