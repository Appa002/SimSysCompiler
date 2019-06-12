#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct StarToken : public IToken{
        StarToken() : IToken() {this->id = Symbol::STAR;}
        std::string getIdentifier() override{
            return "Star(*)";
        }

        friend inline bool operator==(StarToken const & lhs, StarToken const & rhs){
            return true;
        }
    };
}

