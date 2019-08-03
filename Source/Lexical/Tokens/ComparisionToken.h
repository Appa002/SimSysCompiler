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

        explicit ComparisionToken(ComparisionTokenKind kind, size_t lineNum) : kind(kind), IToken(Symbol::CMP, lineNum) {}
        std::string getIdentifier() override{
            return "CMP";
        }

        friend inline bool operator==(ComparisionToken const & lhs, ComparisionToken const & rhs){
            return true;
        }
    };
}

