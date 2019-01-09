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
    protected:
        NewTokenId id;
    public:
        IContext* context;

    };

    enum class NewTokenId{
        VAR
    };
}

#endif //SIMSYSCOMPILER_NEWTOKEN_H
