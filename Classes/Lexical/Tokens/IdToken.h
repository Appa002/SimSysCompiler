#include <utility>

//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_IDTOKEN_H
#define SIMSYSCOMPILER_IDTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct IdToken : public IToken{
        IdToken() : IToken() {id = Symbol::ID;};
        IdToken(std::string sym) : IToken(), sym(std::move(sym)) {id = Symbol::ID;};
        std::string sym;
    };
}

#endif //SIMSYSCOMPILER_VARTOKEN_H
