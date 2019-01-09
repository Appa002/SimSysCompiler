#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_LITERALTOKEN_H
#define SIMSYSCOMPILER_LITERALTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct LiteralToken : public IToken{
        LiteralToken(std::string literal) : IToken(), literal(std::move(literal)) {id = NewTokenId::LITERAL;};
        std::string literal;
    };
}

#endif //SIMSYSCOMPILER_LITERALTOKEN_H
