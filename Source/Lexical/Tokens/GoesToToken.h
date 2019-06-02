//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct GoesToToken : public IToken{
        GoesToToken() : IToken() {id = Symbol::GOES_TO;};

        std::string getIdentifier() override{
            return "goes_to";
        }

        friend inline bool operator==(const GoesToToken&, const GoesToToken&){
            return true;
        }
    };
}