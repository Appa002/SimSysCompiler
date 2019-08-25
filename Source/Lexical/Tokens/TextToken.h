#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct TextToken : public IToken{

        explicit TextToken(size_t lineNum) : IToken(Symbol::TEXT, lineNum) {};

        TextToken(std::string str, size_t lineNum) : data(std::move(str)), IToken(Symbol::TEXT, lineNum) {};

        std::string data;

        std::string getIdentifier() override{
            return "TEXT( "+data+" )";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return data;
        };

        friend inline bool operator==(const TextToken& a, const TextToken& b){
            return a.data == b.data;
        }
    };
}