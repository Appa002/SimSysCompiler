//
// Created by a_mod on 06.01.2019.
//

#pragma once

#include <Stack.h>
#include <Lexical/IToken.h>
#include <functional>
#include <unordered_map>
#include <TypeId.h>
#include <memory>
#include <ScopedSymbolTable.h>

namespace ACC {

    class LexicalAnalysis{
    private:

        std::string buffer;
        int depth = 0;
        std::vector<IToken*> tokens;
        std::string document;
        int refCount = 0;
        std::unordered_map<std::string, TypeId> typesTable;

        ScopedSymbolTable<Symbol>* curScope;
        ScopedSymbolTable<Symbol>* globalScope;

        void preProcessDocument();
        bool isSymbol(std::string idf);
        void emplaceSymbol(std::string idf, Symbol symbol);
        bool isNumber(char c);
        bool isNumber(std::string str);
        TypeId isType(std::string str);
        void pushScope();
        void popScope();
        Symbol getSymbol(std::string sym);

        bool matchIgnoreW(char c, size_t& pos);
        void skipAll(char c, size_t& pos);
        int readUntilNextLine(size_t& pos);
        bool matchAsLongAs(size_t& pos, std::function<bool(void)> condition, std::function<void(void)> body);

        void start (size_t pos, bool shallCheckIndent = false);
        void fn(size_t pos);
        void syscall(size_t pos);
        void exit(size_t pos);
        void var(size_t pos);
        void assignment(size_t pos);
        void expr(size_t& pos, std::vector<std::string> exitTokens);
        void ret(size_t pos);
        void call(size_t pos);
        void type(size_t& pos);
        void parseStringLiteral(size_t &pos);
        void ifStmt(size_t pos);
        void elseStmt(size_t pos);
        void whileStmt(size_t pos);
        void forStmt(size_t pos);
        void declExpr(size_t& pos);


    public:
        LexicalAnalysis() = default;
        explicit LexicalAnalysis(std::string path);
        LexicalAnalysis(const LexicalAnalysis& other);
        ~LexicalAnalysis();
        void printToken();

        const std::vector<IToken*>::iterator begin();
        const std::vector<IToken*>::iterator end();
        std::vector<IToken*> const & data();
    };
}