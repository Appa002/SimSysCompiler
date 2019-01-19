//
// Created by a_mod on 09.01.2019.
//
#pragma once
#include <Lexical/IToken.h>

namespace ACC{
    enum class BracketKind{
        OPEN, CLOSED
    };
    struct BracketToken : public IToken{
        explicit BracketToken(BracketKind k) : IToken(), kind(k) {id = Symbol::BRACKET;};
        BracketKind kind = BracketKind::OPEN;
        friend inline bool operator==(BracketToken const & lhs, BracketToken const & rhs){
            return lhs.kind == rhs.kind;
        }
    };
}