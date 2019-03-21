//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct FunctionToken : public IToken{
        FunctionToken() : IToken() {id = Symbol::FUNCTION;};

        std::string getIdentifier() override{
            return "fn";
        }

        friend inline bool operator==(const FunctionToken&, const FunctionToken&){
            return true;
        }
    };
}

