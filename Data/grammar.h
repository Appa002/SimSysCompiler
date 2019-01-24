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
            stmt,
            start
    };

    bool isNoneterminal(Symbol sys);

    using prodRhs = std::vector<Symbol>;
    using production = std::pair<Symbol, prodRhs>;

    namespace data {
        std::vector<production> getGrammar();

        std::string productionToString(production p);
        std::string symbolToString(Symbol s);
    }
}
#endif //SIMSYSCOMPILER_GRAMMAR_H
