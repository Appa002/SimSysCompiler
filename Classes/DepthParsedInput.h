//
// Created by a_mod on 03.01.2019.
//

#ifndef SIMSYSCOMPILER_EXPRESSIONINPUT_H
#define SIMSYSCOMPILER_EXPRESSIONINPUT_H

#include <Token.h>
#include <vector>
#include <regex>
#include <TokenizedInput.h>

namespace ACC{
    class DepthParsedInput{
        std::vector<Token> data;
        TokenizedInput input;

        bool processed = false;
        bool error = false;
    public:
        explicit DepthParsedInput(TokenizedInput input, bool immediate = true);

        void process();

        std::vector<Token>::iterator begin();
        std::vector<Token>::iterator end();

        void prettyPrint();
    };
}

#endif //SIMSYSCOMPILER_EXPRESSIONINPUT_H
