//
// Created by a_mod on 09.01.2019.
//

#pragma once
#include <Lexical/IToken.h>

namespace ACC{
    struct ModuloToken : public IToken{
        ModuloToken() : IToken() {id = Symbol::MODULO;};

        std::string getIdentifier() override{
            return "Modulo";
        }

        friend inline bool operator==(ModuloToken const&, ModuloToken const&){
            return true;
        }
    };
}

