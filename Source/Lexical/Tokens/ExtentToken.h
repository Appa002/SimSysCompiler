//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ExtentToken : public IToken{
        explicit ExtentToken(size_t lineNum) : IToken(Symbol::EXTENT, lineNum) {};

        std::string getIdentifier() override{
            return "extent";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "closing block";
        };

        friend inline bool operator==(const ExtentToken&, const ExtentToken&){
            return true;
        }
    };
}

