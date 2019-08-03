#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    struct ReturnToken : public IToken{
        explicit ReturnToken(size_t lineNum) : IToken(Symbol::RETURN, lineNum) {}

        std::string getIdentifier() override{
            return "return";
        }

        friend inline bool operator==(ReturnToken const & lhs, ReturnToken const & rhs){
            return true;
        }
    };
}


