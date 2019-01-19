//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_ITOKEN_H
#define SIMSYSCOMPILER_ITOKEN_H

#include <string>
#include <grammar.h>

namespace ACC {
    class IContext;

    class IToken {
    public:
        Symbol id;
        virtual std::string getIdentifier() = 0;
    };

    using token_string = std::vector<IToken*>;

}

#endif //SIMSYSCOMPILER_NEWTOKEN_H
