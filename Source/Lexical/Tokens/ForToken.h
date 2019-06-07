#include <utility>

#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>
#include <General/TypeId.h>

namespace ACC{
    struct ForToken : public IToken{
        ForToken() : IToken() {this->id = Symbol::FOR;}

        std::string getIdentifier() override{
            return "for";
        }

        friend inline bool operator==(ForToken const & lhs, ForToken const & rhs){
            return true;
        }
    };
}

