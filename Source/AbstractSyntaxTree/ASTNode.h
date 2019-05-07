//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ASSNODE_H
#define SIMSYSCOMPILER_ASSNODE_H

#include <initializer_list>
#include <Parser/ParseNode.h>
#include <memory>
#include <GeneralDataStore.h>

enum class AstOperator{
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    LITERAL,
    SEQ,
    ASSIGN,
    ID,
    PRINT,
    EXIT,
    FUNCTION,
    CALL,
    RETURN,
    TYPE_DEF,
    NONE
};

namespace ACC {
    class Expr;
    class Stmt;

    enum class ASTNodeDataType{
        NUMBER,
        STRING,
        OTHER,
        ID
    };

    class ASTNode {
    private:
        std::string astOperator2String(AstOperator op) const;
    public:
        void _print(std::string indent, bool isLast) const;

        ASTNode(AstOperator op, std::vector<ASTNode*> children);
        ASTNode(AstOperator op, GeneralDataStore literal, ASTNodeDataType type);
        ASTNode(AstOperator op, std::string str);
        ASTNode(AstOperator op,  GeneralDataStore store);
        explicit ASTNode(AstOperator op);
        ~ASTNode();

        std::unique_ptr<Expr> asExpr();
        std::vector<ASTNode*> children;

        AstOperator op;
        GeneralDataStore data;
        ASTNodeDataType dataKind = ASTNodeDataType::ID;
    };

}

#endif //SIMSYSCOMPILER_ASSNODE_H
