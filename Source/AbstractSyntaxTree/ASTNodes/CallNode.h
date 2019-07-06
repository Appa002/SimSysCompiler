#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct CallNode : public ASTNode{
        std::shared_ptr<Structure> generate(ACC::Code &code) override;
        CallNode(AstOperator op, std::vector<ASTNode *> children);
        std::vector<Type> getArgumentTypes();

        bool isPerfectMatch(std::vector<std::shared_ptr<Structure>> values, Fn &overload);
        bool isConvertable(std::vector<std::shared_ptr<Structure>> values, Fn &overload);

    };
}

