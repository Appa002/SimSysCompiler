//
// Created by a_mod on 06.01.2019.
//

#pragma once

#include <General/Stack.h>
#include <Lexical/IToken.h>
#include <functional>
#include <unordered_map>
#include <General/Type.h>
#include <memory>
#include <General/ScopedSymbolTable.h>
#include <list>

namespace ACC {

    class LexicalAnalysis{
    private:

        std::vector<IToken*> tokens;
        std::string document;
        int refCount = 0;
        std::vector<size_t> indentList;
        int depth = 0;

        void postProcessDocument();

        int readDepth(size_t& pos);
        void analyse();
        void checkIndent(size_t &idx, size_t lineNum);

        bool checkSpecial(const std::string &buffer, size_t lineNum);
        bool checkKeyword(std::string const &buffer, size_t lineNum);

        std::string loadBuffer(size_t &idx);

    public:
        LexicalAnalysis() = default;
        explicit LexicalAnalysis(std::string path);
        ~LexicalAnalysis();

        void printToken();

        const std::vector<IToken*>::iterator begin();
        const std::vector<IToken*>::iterator end();
        std::vector<IToken*> const & data();

        void addZeroExit();

    };
}