//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_MATHOPERATORTOKEN_H
#define SIMSYSCOMPILER_MATHOPERATORTOKEN_H

#include <Lexical/IToken.h>
#include <stdexcept>

namespace ACC{
    enum class MathOperators{
        PLUS, MINUS
    };
    struct MathOperatorToken : public IToken{
        MathOperatorToken(MathOperators k) : IToken(), kind(k) {id = Symbol::MATH_OPERATOR;};
        MathOperators kind;

        std::string getIdentifier() override{
            switch (kind){
                case MathOperators::PLUS:
                    return "MathToken (+)";
                case MathOperators::MINUS:
                    return "MathToken (-)";
            }
            throw std::runtime_error("Kind of MathOperatorToken is unknown value");
        }

        friend inline bool operator==(MathOperatorToken const & lhs, MathOperatorToken const & rhs){
                return lhs.kind == rhs.kind;
        }
    };
}


#endif //SIMSYSCOMPILER_MATHOPERATORTOKEN_H
