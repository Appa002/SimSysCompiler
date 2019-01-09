#include <utility>

//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_VARTOKEN_H
#define SIMSYSCOMPILER_VARTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct VarToken : public IToken{
        VarToken() : IToken() {id = NewTokenId::VAR;};
        VarToken(std::string sym) : IToken(), sym(std::move(sym)) {id = NewTokenId::VAR;};
        std::string sym;
    };
}

#endif //SIMSYSCOMPILER_VARTOKEN_H
