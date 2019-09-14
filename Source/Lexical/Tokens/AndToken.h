//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct AndToken : public IToken{
        explicit AndToken(size_t lineNum) : IToken(Symbol::AND, lineNum) {};

        std::string getIdentifier() override{
            return "&&";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "&&";
        };

        friend inline bool operator==(const AndToken&, const AndToken&){
            return true;
        }
    };
}