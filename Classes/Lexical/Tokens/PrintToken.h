#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_PRINTTOKEN_H
#define SIMSYSCOMPILER_PRINTTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct PrintToken : public IToken{
        PrintToken(std::string s) : IToken(), sym(std::move(s)) {this->id = Symbol::PRINT;}
        std::string sym;
    };
}


#endif //SIMSYSCOMPILER_PRINTTOKEN_H
