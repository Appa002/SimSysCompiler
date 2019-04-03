//
// Created by a_mod on 06.01.2019.
//

#pragma once

#include <Stack.h>
#include <Lexical/IToken.h>
#include <functional>
#include <unordered_map>

namespace ACC {
    class LexicalAnalysis{
    private:

        std::string buffer;
        int depth = 0;
        std::vector<IToken*> tokens;
        std::string document;
        int refCount = 0;
        bool processed = false;
        std::unordered_map<std::string, Symbol> table;

        void preProcessDocument();
        bool inTable(std::string idf);
        bool isNumber(char c);
        bool isNumber(std::string str);
        bool matchIgnoreW(char c, size_t& pos);
        void skipAll(char c, size_t& pos);
        int readUntilNextLine(size_t& pos);
        bool matchAsLongAs(size_t& pos, std::function<bool(void)> condition, std::function<void(void)> body);

        void start (size_t pos, bool shallCheckIndent = false);
        void fn(size_t pos);
        void print(size_t pos);
        void exit(size_t pos);
        void var(size_t pos);
        void expr(size_t& pos, std::vector<std::string> exitTokens);
        void ret(size_t pos);
        void call(size_t pos);


    public:
        explicit LexicalAnalysis(std::string path);
        LexicalAnalysis(const LexicalAnalysis& other);
        ~LexicalAnalysis();
        void printToken();

        const std::vector<IToken*>::iterator begin();
        const std::vector<IToken*>::iterator end();
        std::vector<IToken*> const & data();
    };
}