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
#include <General/LineCountingPosition.h>

namespace ACC {
    class LexicalAnalysis{
    private:

        std::vector<IToken*> tokens;
        std::string document;
        int refCount = 0;
        std::vector<size_t> indentList;
        int depth = 0;
        bool stringMode = false;

        void postProcessDocument();

        int readDepth(LineCountingPosition& pos);
        void analyse();
        void checkIndent(LineCountingPosition &idx);

        void findLines(std::vector<std::string> & lines);

        bool checkSpecial(const std::string &buffer, LineCountingPosition idx,
                                  const std::vector<std::string> &lines);
        bool checkKeyword(std::string const &buffer, LineCountingPosition idx,
                                  const std::vector<std::string> &lines);

        std::string loadBuffer(LineCountingPosition &idx);

    public:
        LexicalAnalysis() = default;

        LexicalAnalysis(LexicalAnalysis const & other);

        explicit LexicalAnalysis(std::string path);
        ~LexicalAnalysis();

        void printToken();

        const std::vector<IToken*>::iterator begin();
        const std::vector<IToken*>::iterator end();
        IToken* at(size_t idx);
        size_t size();
        std::vector<IToken*> const & data();

        void addZeroExit();

    };
}