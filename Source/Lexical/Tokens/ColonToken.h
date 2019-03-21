//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ColonToken : public IToken{
        ColonToken() : IToken() {id = Symbol::COLON;};

        std::string getIdentifier() override{
            return "colon";
        }

        friend inline bool operator==(const ColonToken&, const ColonToken&){
            return true;
        }
    };
}

