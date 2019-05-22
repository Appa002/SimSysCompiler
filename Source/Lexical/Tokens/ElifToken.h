//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ElifToken : public IToken{
        ElifToken() : IToken() {id = Symbol::ELIF;};

        std::string getIdentifier() override{
            return "elif";
        }

        friend inline bool operator==(const ElifToken&, const ElifToken&){
            return true;
        }
    };
}