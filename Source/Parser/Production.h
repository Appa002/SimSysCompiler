//
// Created by a_mod on 25.01.2019.
//

#ifndef SIMSYSCOMPILER_PRODUCTION_H
#define SIMSYSCOMPILER_PRODUCTION_H

#include <vector>

namespace ACC {
    enum class Symbol : int{
        empty = -1,
        VAR = 0,
        DECL,
        TEXT,
        IMPORT,
        DOUBLE_QUOTE,
        QUOTE,
        MODULO,
        ELIF,
        ARROW,
        DOT,
        FOR,
        ID,
        SALLOC,
        CMP,
        OPEN_BRACKET,
        CLOSED_BRACKET,
        OPEN_CURLY,
        CLOSED_CURLY,
        SYSCALL,
        LITERAL,
        ASSIGN,
        EOS,
        EXIT,
        INDENT,
        EXTENT,
        FUNCTION,
        COLON,
        COMMA,
        RETURN,
        TYPE,
        IF,
        NOT,
        ELSE,
        WHILE,
        SLASH,
        STAR,
        PLUS,
        MINUS,

        ptr_assign,
        for_construct,
        while_construct,
        if_construct,
        expr,
        assignment,
        keyword,
        stmt,
        start,
        function,
        paramsDecl,
        paramsList,
        call,
        ifStmt,
        else_construct,
        elseIf_construct,
        type,

        __debug_escape_sequence
    };

    using productionBody_t = std::vector<Symbol>;

    struct Production {
        Production() = default;
        explicit Production(Symbol head);
        Production(Symbol head, std::vector<Symbol> body);

        Symbol head = Symbol::empty;
        std::vector<Symbol> body;
    };
}

#endif //SIMSYSCOMPILER_PRODUCTION_H
