#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct WhileToken : public IToken{
        WhileToken() : IToken() {this->id = Symbol::WHILE;}
        std::string getIdentifier() override{
            return "While";
        }

        friend inline bool operator==(WhileToken const & lhs, WhileToken const & rhs){
            return true;
        }
    };
}

