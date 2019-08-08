//
// Created by a_mod on 09.02.2019.
//

#ifndef SIMSYSCOMPILER_DECLTOKEN_H
#define SIMSYSCOMPILER_DECLTOKEN_H


#include <Lexical/IToken.h>

namespace ACC{
    struct DeclToken : public IToken{
        explicit DeclToken(size_t lineNum) : IToken(Symbol::DECL, lineNum) {};
        DeclToken(std::string sym, size_t lineNum) : IToken(Symbol::DECL, lineNum), sym(std::move(sym)) {};
        std::string sym;

        std::string getIdentifier() override{
            return "Decl ("+sym+")";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return sym;
        };

        friend inline bool operator==(DeclToken const & lhs, DeclToken const & rhs){
            return lhs.sym == rhs.sym;
        }
    };
}


#endif //SIMSYSCOMPILER_DECLTOKEN_H
