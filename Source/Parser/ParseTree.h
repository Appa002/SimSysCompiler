//
// Created by a_mod on 10.01.2019.
//

#pragma once

#include <Lexical/LexicalAnalysis.h>
#include "ParseNode.h"
#include "Production.h"


namespace ACC {
    class ParseTree {
    private:
        void killChildren(ParseNode* node);

        ParseNode * root = nullptr;
        int refCount = 1;
        bool generated = false;
    public:
        ParseTree() = default;
        explicit ParseTree(const LexicalAnalysis& in);
        ParseTree(ParseTree const & other);
        ~ParseTree();

        ParseNode const* getRoot();
        void generate(LexicalAnalysis in);

    private:
        std::vector<IToken*> document;

        ParseNode* match(size_t& pos, Symbol what);

        ParseNode* start(size_t& pos);
        ParseNode* assignment(size_t& pos);
        ParseNode* function(size_t& pos);
        ParseNode* keyword(size_t& pos);
        ParseNode* call(size_t& pos);
        ParseNode* expr(size_t& pos);
        ParseNode* paramDecl(size_t &pos);
        ParseNode* paramList(size_t &pos);
        ParseNode* ifConstruct(size_t &pos);
        ParseNode* elifConstruct(size_t &pos);
        ParseNode* elseConstruct(size_t &pos);
        ParseNode* whileConstruct(size_t &pos);
        ParseNode* forConstruct(size_t &pos);

    };
}
