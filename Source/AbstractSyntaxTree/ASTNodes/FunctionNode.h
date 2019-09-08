#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct FunctionNode : public ASTNode{
        std::shared_ptr<Structure> generate(ACC::Code &code) override;
        FunctionNode(AstOperator op, std::vector<ASTNode *> children);

        std::string copyIntoStackFrame(size_t offset, size_t loc, size_t size, ACC::Code &code);

        void checkIfReserved(std::string const & name);

        std::vector<Type> getArgumentTypes();
    };
}

