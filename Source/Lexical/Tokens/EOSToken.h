//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_BRAKETTOKEN_H
#define SIMSYSCOMPILER_BRAKETTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct EOSToken : public IToken{
        explicit EOSToken(size_t lineNum) : IToken(Symbol::EOS, lineNum) {};

        std::string getIdentifier() override{
            return "EndOfStatement";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return ";";
        };

        friend inline bool operator==(EOSToken const&, EOSToken const&){
            return true;
        }
    };
}

#endif //SIMSYSCOMPILER_BRAKETTOKEN_H
