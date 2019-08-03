#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct TextToken : public IToken{

        explicit TextToken(size_t lineNum) : IToken(Symbol::ARROW, lineNum) {};

        TextToken(std::string str, size_t lineNum) : data(std::move(str)), IToken(Symbol::ARROW, lineNum) {};

        std::string data;

        std::string getIdentifier() override{
            return "TEXT( "+data+" )";
        }

        friend inline bool operator==(const TextToken&, const TextToken&){
            return true;
        }
    };
}