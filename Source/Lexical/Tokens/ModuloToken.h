//
// Created by a_mod on 09.01.2019.
//

#pragma once
#include <Lexical/IToken.h>

namespace ACC{
    struct ModuloToken : public IToken{
        explicit ModuloToken(size_t lineNum) : IToken(Symbol::MODULO, lineNum) {};

        std::string getIdentifier() override{
            return "Modulo";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "%";
        };

        friend inline bool operator==(ModuloToken const&, ModuloToken const&){
            return true;
        }
    };
}

