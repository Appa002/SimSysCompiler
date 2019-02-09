//
// Created by a_mod on 09.02.2019.
//

#ifndef SIMSYSCOMPILER_DECLTOKEN_H
#define SIMSYSCOMPILER_DECLTOKEN_H


#include <Lexical/IToken.h>

namespace ACC{
    struct DeclToken : public IToken{
        DeclToken() : IToken() {id = Symbol::DECL;};
        DeclToken(std::string sym) : IToken(), sym(std::move(sym)) {id = Symbol::DECL;};
        std::string sym;

        std::string getIdentifier() override{
            return "Decl ("+sym+")";
        }

        friend inline bool operator==(DeclToken const & lhs, DeclToken const & rhs){
            return lhs.sym == rhs.sym;
        }
    };
}


#endif //SIMSYSCOMPILER_DECLTOKEN_H
