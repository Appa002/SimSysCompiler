//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ASSNODE_H
#define SIMSYSCOMPILER_ASSNODE_H

#include <initializer_list>
#include <Parser/ParseNode.h>
#include <memory>
#include <GeneralDataStore.h>
#include <TypeId.h>
#include <Structure/Structure.h>

namespace ACC {


    enum class ComparisionType {
        EQ, // Equal
        LT, // Less then
        GT, // Greater then
        NEQ, // Not equal
        LET, // Less or Equal Then
        GET // Greater or Equal Then
    };

    enum class AstOperator {
        PLUS,
        NOT,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        LITERAL,
        SEQ,
        ASSIGN,
        REASSIGN,
        ID,
        SYSCALL,
        EXIT,
        FUNCTION,
        CALL,
        RETURN,
        TYPE_DEF,
        IF_CONSTRUCT,
        IF,
        ELIF,
        ELSE,
        EQUAL,
        NOT_EQUAL,
        LESS,
        GREATER,
        LESS_EQUAL,
        GREATER_EQUAL,
        WHILE,
        FOR,

        __NONE,
        __CONTAINER
    };

    class ASTNode {
    private:
        std::string astOperator2String(AstOperator op) const;

    public:
        void _print(std::string indent, bool isLast) const;

        ASTNode(AstOperator op, std::vector<ASTNode *> children);
        ASTNode(AstOperator op, GeneralDataStore literal, TypeId type);
        ASTNode(AstOperator op, std::string str);
        ASTNode(AstOperator op, GeneralDataStore store);

        explicit ASTNode(AstOperator op);

        ~ASTNode();

        virtual std::shared_ptr<Structure> generate(Code &code);

        std::vector<ASTNode *> children;

        AstOperator op;
        GeneralDataStore data;
        TypeId type;
    };

}

#endif //SIMSYSCOMPILER_ASSNODE_H
