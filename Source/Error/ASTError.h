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
    class ASTError : public std::exception {
    public:
        ASTError(size_t lineNum, std::string  lineContent, std::string msg) :
                lineNum(lineNum), lineContent(std::move(lineContent)),msg(std::move(msg)) {}

        explicit ASTError(std::string msg) : msg(std::move(msg)) {}

        size_t lineNum = 0;
        std::string lineContent = "";
        const std::string msg;
    };


}