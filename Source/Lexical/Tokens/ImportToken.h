//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ImportToken : public IToken{
        explicit ImportToken(size_t lineNum) : IToken(Symbol::IMPORT, lineNum) {};

        std::string getIdentifier() override{
            return "import";
        }

        friend inline bool operator==(const ImportToken&, const ImportToken&){
            return true;
        }
    };
}