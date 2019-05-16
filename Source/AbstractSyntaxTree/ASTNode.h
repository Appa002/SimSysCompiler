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

enum class AstOperator{
    PLUS,
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
    IF,
    EQUAL,
    NOT_EQUAL,
    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL,

    __NONE,
    __CONTAINER
};

namespace ACC {
    class Expr;
    class Stmt;

    class ASTNode {
    private:
        std::string astOperator2String(AstOperator op) const;
    public:
        void _print(std::string indent, bool isLast) const;

        ASTNode(AstOperator op, std::vector<ASTNode*> children);
        ASTNode(AstOperator op, GeneralDataStore literal, TypeId type);
        ASTNode(AstOperator op, std::string str);
        ASTNode(AstOperator op,  GeneralDataStore store);
        explicit ASTNode(AstOperator op);
        ~ASTNode();

        std::unique_ptr<Expr> asExpr();
        std::vector<ASTNode*> children;

        AstOperator op;
        GeneralDataStore data;
        TypeId type;
    };

}

#endif //SIMSYSCOMPILER_ASSNODE_H
