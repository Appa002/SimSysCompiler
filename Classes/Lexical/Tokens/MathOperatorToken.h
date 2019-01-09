//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_MATHOPERATORTOKEN_H
#define SIMSYSCOMPILER_MATHOPERATORTOKEN_H

#include <Lexical/IToken.h>

namespace ACC{
    enum class MathOperators{
        PLUS, MINUS
    };
    struct MathOperatorToken : public IToken{
        MathOperatorToken(MathOperators k) : IToken(), kind(k) {id = NewTokenId::MATH_OPERATOR;};
        MathOperators kind;
    };
}


#endif //SIMSYSCOMPILER_MATHOPERATORTOKEN_H
