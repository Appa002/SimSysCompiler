#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct AssignToken : public IToken{
        AssignToken() : IToken() {this->id = Symbol::ASSIGN;}
        std::string getIdentifier() override{
            return "Assign";
        }

        friend inline bool operator==(AssignToken const & lhs, AssignToken const & rhs){
            return true;
        }
    };
}

