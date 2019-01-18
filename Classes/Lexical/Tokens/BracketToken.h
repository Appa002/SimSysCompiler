//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_BRAKETTOKEN_H
#define SIMSYSCOMPILER_BRAKETTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    enum class BracketKind{
        OPEN, CLOSED
    };
    struct BracketToken : public IToken{
        BracketToken(BracketKind k) : IToken(), kind(k) {id = Symbol::BRACKET;};
        BracketKind kind = BracketKind::OPEN;
    };
}

#endif //SIMSYSCOMPILER_BRAKETTOKEN_H
