//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_VARTOKEN_H
#define SIMSYSCOMPILER_VARTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct VarToken : public IToken{
        explicit VarToken(size_t lineNum) : IToken(Symbol::VAR, lineNum) {};

        std::string getIdentifier() override{
            return "var";
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "var";
        };

        friend inline bool operator==(const VarToken&, const VarToken&){
            return true;
        }
    };
}

#endif //SIMSYSCOMPILER_VARTOKEN_H
