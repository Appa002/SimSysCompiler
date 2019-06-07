//
// Created by a_mod on 14.05.2019.
//
#pragma once

#include <string>
#include <unordered_map>

namespace ACC {
    template<class T>
    class ScopedSymbolTable {
    public:
        ScopedSymbolTable(){

        };
        explicit ScopedSymbolTable(ScopedSymbolTable *prev);
        ~ScopedSymbolTable() {
            delete next;
        }

        bool isSymbol(std::string const &sym);
        bool isSymbolInThisScope(std::string const & sym);
        T& getSymbol(std::string const &sym);

        std::unordered_map<std::string, T> symbolTable;
        ScopedSymbolTable *prev = nullptr;
        ScopedSymbolTable *next = nullptr;
    };

    template<class T>
    T& ScopedSymbolTable<T>::getSymbol(std::string const &sym) {
        if (symbolTable.find(sym) != symbolTable.cend())
            return symbolTable.at(sym);
        if (prev == nullptr)
            throw std::runtime_error("Symbol not in table!");
        return prev->getSymbol(sym);
    }

    template<class T>
    bool ScopedSymbolTable<T>::isSymbol(std::string const &sym) {
        if (symbolTable.find(sym) != symbolTable.cend())
            return true;
        if (prev == nullptr)
            return false;
        return prev->isSymbol(sym);
    }

    template<class T>
    ScopedSymbolTable<T>::ScopedSymbolTable(ScopedSymbolTable *prev)  : prev(prev) {
        prev->next = this;
    }

    template<class T>
    bool ScopedSymbolTable<T>::isSymbolInThisScope(std::string const &sym) {
        if (symbolTable.find(sym) != symbolTable.cend())
            return true;
        return false;
    }

}
