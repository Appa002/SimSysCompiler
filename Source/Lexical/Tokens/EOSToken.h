//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_BRAKETTOKEN_H
#define SIMSYSCOMPILER_BRAKETTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct EOSToken : public IToken{
        EOSToken() : IToken() {id = Symbol::EOS;};
        friend inline bool operator==(EOSToken const&, EOSToken const&){
            return true;
        }
    };
}

#endif //SIMSYSCOMPILER_BRAKETTOKEN_H
