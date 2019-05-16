//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct IfToken : public IToken{
        IfToken() : IToken() {id = Symbol::IF;};

        std::string getIdentifier() override{
            return "if";
        }

        friend inline bool operator==(const IfToken&, const IfToken&){
            return true;
        }
    };
}