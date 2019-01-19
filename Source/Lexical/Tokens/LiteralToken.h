#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_LITERALTOKEN_H
#define SIMSYSCOMPILER_LITERALTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct LiteralToken : public IToken{
        LiteralToken(std::string literal) : IToken(), literal(std::move(literal)) {id = Symbol::LITERAL;};
        std::string literal;

        std::string getIdentifier() override {
            return "Literal (" + literal + ")";
        }

        friend inline bool operator==(LiteralToken const & lhs, LiteralToken const & rhs){
            return lhs.literal == rhs.literal;
        }
    };
}

#endif //SIMSYSCOMPILER_LITERALTOKEN_H
