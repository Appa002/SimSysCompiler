#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct PlusToken : public IToken{
        PlusToken() : IToken() {this->id = Symbol::PLUS;}
        std::string getIdentifier() override{
            return "Plus";
        }

        friend inline bool operator==(PlusToken const & lhs, PlusToken const & rhs){
            return true;
        }
    };
}

