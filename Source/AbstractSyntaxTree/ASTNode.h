//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ASSNODE_H
#define SIMSYSCOMPILER_ASSNODE_H

#include <initializer_list>
#include <Parser/ParseNode.h>

enum class AstOperator{
    PLUS,
    MINUS,
    LITERAL,
    STMT,
    ASSIGN,
    ID,
    PRINT
};

namespace ACC {
    class ASTNode {
        AstOperator op;
        std::vector<ASTNode*> children;
        std::string str;
        void _print(std::string indent, bool isLast) const;
        std::string astOperator2String(AstOperator op) const;
            public:
        ASTNode(AstOperator op, std::vector<ASTNode*> children);
        ASTNode(AstOperator op, std::string str);
        void print();
    };

}

#endif //SIMSYSCOMPILER_ASSNODE_H
