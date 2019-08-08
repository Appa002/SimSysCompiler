//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct IfToken : public IToken{
        explicit IfToken(size_t lineNum) : IToken(Symbol::IF, lineNum) {};

        std::string getIdentifier() override{
            return "if";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "if";
        };

        friend inline bool operator==(const IfToken&, const IfToken&){
            return true;
        }
    };
}