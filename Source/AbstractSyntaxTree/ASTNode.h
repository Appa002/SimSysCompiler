//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ASSNODE_H
#define SIMSYSCOMPILER_ASSNODE_H

#include <initializer_list>
#include <Parser/ParseNode.h>
#include <memory>

enum class AstOperator{
    PLUS,
    MINUS,
    LITERAL,
    SEQ,
    ASSIGN,
    ID,
    PRINT
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
        ASTNode(AstOperator op, std::string str);
        ~ASTNode();

        std::unique_ptr<Expr> asExpr();
        std::vector<ASTNode*> children;

        AstOperator op;
        std::string str;
    };

}

#endif //SIMSYSCOMPILER_ASSNODE_H
