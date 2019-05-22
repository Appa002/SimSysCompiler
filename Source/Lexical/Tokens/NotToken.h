#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct NotToken : public IToken{
        NotToken() : IToken() {this->id = Symbol::NOT;}
        std::string getIdentifier() override{
            return "Not";
        }

        friend inline bool operator==(NotToken const & lhs, NotToken const & rhs){
            return true;
        }
    };
}

