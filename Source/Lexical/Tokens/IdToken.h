#include <utility>

//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_IDTOKEN_H
#define SIMSYSCOMPILER_IDTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct IdToken : public IToken{
        explicit IdToken(size_t lineNum) : IToken(Symbol::ID, lineNum) {};
        IdToken(std::string sym, size_t lineNum) : IToken(Symbol::ID, lineNum), sym(std::move(sym)) {};
        std::string sym;

        std::string getIdentifier() override{
            return "Id ("+sym+")";
        }
        [[nodiscard]] std::string getIdForErrReporting() const override{
            return sym;
        };

        friend inline bool operator==(IdToken const & lhs, IdToken const & rhs){
            return lhs.sym == rhs.sym;
        }
    };
}

#endif //SIMSYSCOMPILER_VARTOKEN_H
