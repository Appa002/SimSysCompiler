#include <utility>

//
// Created by a_mod on 02.01.2019.
//

#ifndef SIMSYSCOMPILER_TOKENS_H
#define SIMSYSCOMPILER_TOKENS_H

#include <string>
#include <vector>

namespace ACC{
    enum class TokenId;

    struct Token{
        Token(TokenId t, long p, std::string s, std::vector<Token> sT = {})
        : id(t), pos(p), content(std::move(s)), subToken(std::move(sT)) {};
        TokenId id;
        long pos;
        std::string content;
        std::vector<Token> subToken;

        friend inline bool operator==(const Token& lhs, const Token& rhs){
            return lhs.id == rhs.id && lhs.content == rhs.content && lhs.pos == rhs.pos;
        }

        friend inline bool operator!=(const Token& lhs, const Token& rhs){
            return !(lhs == rhs);
        }
    };

    enum class TokenId{
            TOKEN_VAR, // var
            TOKEN_ASSIGN, // =
            TOKEN_EOE, // ;
            TOKEN_PLUS, // +
            TOKEN_MINUS, // -
            TOKEN_PRINT, // print
            TOKEN_OPEN_BRACKET, // (
            TOKEN_CLOSED_BRACKET, // )
            TOKEN_NEWLINE, // \n
            TOKEN_UNKNOWN,
            TOKEN_ENCLOSING_BRACKETS // ( ... )
        };
}

//                 {Token::TOKEN_ENCLOSING_BRACKETS, std::regex("(\\(.+?\\))")},

#endif //SIMSYSCOMPILER_TOKENS_H