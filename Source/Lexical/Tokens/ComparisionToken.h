#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{

    enum class ComparisionTokenKind{
        Equal,
        NotEqual,
        Less,
        Greater,
        LessEqual,
        GreaterEqual
    };

    struct ComparisionToken : public IToken{
        ComparisionTokenKind kind;

        explicit ComparisionToken(ComparisionTokenKind kind) : kind(kind), IToken() {this->id = Symbol::CMP;}
        std::string getIdentifier() override{
            return "Equal";
        }

        friend inline bool operator==(ComparisionToken const & lhs, ComparisionToken const & rhs){
            return true;
        }
    };
}

