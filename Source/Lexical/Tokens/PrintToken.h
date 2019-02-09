#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_PRINTTOKEN_H
#define SIMSYSCOMPILER_PRINTTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    struct PrintToken : public IToken{
        PrintToken() : IToken() {this->id = Symbol::PRINT;}
        std::string getIdentifier() override{
            return "print";
        }

        friend inline bool operator==(PrintToken const & lhs, PrintToken const & rhs){
            return true;
        }
    };
}


#endif //SIMSYSCOMPILER_PRINTTOKEN_H
