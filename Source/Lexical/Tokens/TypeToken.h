#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct TypeToken : public IToken{

        explicit TypeToken(size_t lineNum) : IToken(Symbol::TYPE, lineNum) {};

        std::string data;

        std::string getIdentifier() override{
            return "TYPE";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "TYPE";
        };

        friend inline bool operator==(const TypeToken&, const TypeToken&){
            return true;
        }
    };
}