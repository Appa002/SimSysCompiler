//
// Created by a_mod on 19.01.2019.
//

#ifndef SIMSYSCOMPILER_REGULAR_EXPRESSIONS_H
#define SIMSYSCOMPILER_REGULAR_EXPRESSIONS_H

#include <Lexical/Pattern.h>

namespace ACC{
    namespace data{
        const auto print_pattern = Pattern({"[a-zA-Z_]+| +[a-zA-Z_]+"});
        const auto id_pattern = Pattern({"[a-zA-Z_]+ | +[a-zA-Z_]+ "});
        const auto var_pattern = Pattern({"var| +var"});
        const auto printKeyword_pattern = Pattern({"print"});
        const auto assigment_pattern = Pattern({"="});
        const auto numberLiteral_pattern = Pattern({" +[0-9]+|[0-9]+"});
        const auto plus_pattern = Pattern({"\\+| +\\+"});
        const auto minus_pattern = Pattern({"-| +-"});
        const auto openBracket_pattern = Pattern({"\\(| +\\("});
        const auto closedBracket_pattern = Pattern({"\\)| +\\)"});

    }
}

#endif //SIMSYSCOMPILER_REGULAR_EXPRESSIONS_H
