//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct CommaToken : public IToken{
        CommaToken() : IToken() {id = Symbol::COMMA;};

        std::string getIdentifier() override{
            return "comma";
        }

        friend inline bool operator==(const CommaToken&, const CommaToken&){
            return true;
        }
    };
}

