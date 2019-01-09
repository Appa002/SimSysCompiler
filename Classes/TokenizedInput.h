#include <utility>

//
// Created by a_mod on 02.01.2019.
//

#ifndef SIMSYSCOMPILER_TOKENIZEDINPUT_H
#define SIMSYSCOMPILER_TOKENIZEDINPUT_H

#include <vector>
#include <iterator>
#include <fstream>
#include <Token.h>
#include <regex>

namespace ACC {
    class TokenizedInput {
    private:
        std::vector<Token> data;
        std::ifstream* inputFile;
        bool processed = false;
        bool error = false;
        std::vector<std::pair<TokenId, std::regex>> token2regex;

        void buildLexicon(std::string lexicon);
        void split(std::string str, char determinator, std::string &lhs, std::string &rhs);
        std::string cleanStr(std::string in);

    public:
        explicit TokenizedInput(std::ifstream* inputFile, bool immediate = true, std::string lexicon = "./grammar.lex");

        static void prettyPrint(TokenizedInput& input, const int space = 10);

        TokenizedInput process();

        std::vector<Token>::iterator begin();
        std::vector<Token>::iterator end();
    };
}

#endif //SIMSYSCOMPILER_TOKENIZEDINPUT_H
