#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct MinusToken : public IToken{
        MinusToken() : IToken() {this->id = Symbol::MINUS;}
        std::string getIdentifier() override{
            return "Minus";
        }

        friend inline bool operator==(MinusToken const & lhs, MinusToken const & rhs){
            return true;
        }
    };
}

