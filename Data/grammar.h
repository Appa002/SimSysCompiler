//
// Created by a_mod on 18.01.2019.
//

#ifndef SIMSYSCOMPILER_GRAMMAR_H
#define SIMSYSCOMPILER_GRAMMAR_H

#include <string>
#include <Parser/Production.h>

namespace ACC {

    bool isNoneterminal(Symbol sys);

    namespace data {
        std::vector<Production> getGrammar();

        std::string productionToString(Production p);
        std::string symbolToString(Symbol s);
    }
}
#endif //SIMSYSCOMPILER_GRAMMAR_H
