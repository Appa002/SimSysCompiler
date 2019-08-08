//
// Created by a_mod on 08.08.2019.
//

#pragma once

#include <stdexcept>
#include <string>
#include <utility>

namespace ACC{
    class IToken;
    enum class Symbol;
}

namespace ACC::errors {
    class SyntaxError : public std::exception {
    public:
        SyntaxError(size_t lineNum, std::string  lineContent, IToken* unexpected, Symbol expected) :
            lineNum(lineNum), lineContent(std::move(lineContent)), unexpected(unexpected), expected(expected){}

        const size_t lineNum;
        const std::string lineContent;
        const IToken* unexpected;
        const Symbol expected;
    };


}