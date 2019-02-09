//
// Created by a_mod on 27.01.2019.
//

#ifndef SIMSYSCOMPILER_SYMBOLTABLE_H
#define SIMSYSCOMPILER_SYMBOLTABLE_H

#include <Singleton.h>
#include <unordered_map>
#include <Lexical/IToken.h>

namespace ACC {
    class SymbolTable : public Singleton<SymbolTable>, public std::unordered_map<std::string, Symbol>{
    public:
        SymbolTable();
    };
}

#endif //SIMSYSCOMPILER_SYMBOLTABLE_H
