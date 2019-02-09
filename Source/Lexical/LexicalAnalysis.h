//
// Created by a_mod on 06.01.2019.
//

#pragma once

#include <Stack.h>
#include <Lexical/IToken.h>

namespace ACC {
    class LexicalAnalysis{
    private:
        std::vector<IToken*> tokens;
        std::string document;
        int refCount = 0;
        bool processed = false;

        void preProcessDocument();
        bool inTable(std::string idf);
        bool isNumber(char c);
    public:
        explicit LexicalAnalysis(std::string path);
        LexicalAnalysis(const LexicalAnalysis& other);
        ~LexicalAnalysis();
        void process();
        void printToken();

        const std::vector<IToken*>::iterator begin();
        const std::vector<IToken*>::iterator end();
        std::vector<IToken*> const & data();
    };
}