//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_ITOKEN_H
#define SIMSYSCOMPILER_ITOKEN_H

#include <string>

namespace ACC {
    class IContext;
    enum class NewTokenId;

    class IToken {
    public:
        NewTokenId id;
    };

    enum class NewTokenId{
        VAR,
        ID,
        BRACKET,
        MATH_OPERATOR,
        PRINT,
        LITERAL,
        EOS
    };
}

#endif //SIMSYSCOMPILER_NEWTOKEN_H
