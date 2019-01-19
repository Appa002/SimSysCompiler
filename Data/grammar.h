//
// Created by a_mod on 18.01.2019.
//

#ifndef SIMSYSCOMPILER_GRAMMAR_H
#define SIMSYSCOMPILER_GRAMMAR_H

#include <vector>
#include <string>

namespace ACC {
    enum class Symbol {
            VAR,
            ID,
            BRACKET,
            MATH_OPERATOR,
            PRINT,
            LITERAL,
            EOS,

            none_terminals_start,

            expr,
            stmt
    };

    bool isNoneterminal(Symbol sys);

    using production = std::vector<Symbol>;
    using definition = std::pair<Symbol, production>;

    namespace data {
        std::vector<definition> getGrammar();
        std::string symbolToString(Symbol s);
    }
}
#endif //SIMSYSCOMPILER_GRAMMAR_H
