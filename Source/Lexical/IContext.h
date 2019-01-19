//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_ICONTEXT_H
#define SIMSYSCOMPILER_ICONTEXT_H

#include <vector>
#include <functional>
#include <Lexical/IToken.h>
#include <Lexical/Pattern.h>
#include "Instruction.h"

namespace ACC {
    class IContext {
    public:
        using evaluator = std::function<IToken*(const std::string&, const std::string::iterator&, const std::string::iterator&)>;
        using context_switcher = std::function<IContext*(void)>;
        using match = std::pair<Pattern, Instruction>;

        virtual const std::vector<match> getLegals() = 0;
        virtual Pattern escapeSequence() = 0;
        virtual ~IContext() = default;
    };
}

#endif //SIMSYSCOMPILER_ICONTEXT_H
