//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ExtentToken : public IToken{
        ExtentToken() : IToken() {id = Symbol::EXTENT;};

        std::string getIdentifier() override{
            return "extent";
        }

        friend inline bool operator==(const ExtentToken&, const ExtentToken&){
            return true;
        }
    };
}

