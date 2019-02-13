//
// Created by a_mod on 11.02.2019.
//

#include <IntermediateCodeGenerator/Optimizaions/Optimizations.h>
#include <Logger/Logger.h>
#include "Utils.h"
using namespace ACC;
/*
std::vector<Tuple<Operator*, size_t >> fetchSignificantOps(Code& input){
    std::vector<Tuple<Operator*, size_t >> out;
    size_t i = 0;
    for(auto& op : input){
        if(op.id == OperatorId::PRINT)
            out.push_back({&input.at(i), i});
        i++;
    }
    return out;
}

void doElision(DependencyElement* root){
    if(root->lhs != nullptr && root->rhs == nullptr && root->lhs->op->id == OperatorId::COPY){
        root->op->lhs = root->lhs->lhs->op->result;
       root->lhs->dead = true;
    }
    if(root->lhs != nullptr)
        doElision(root->lhs);
    if(root->rhs != nullptr)
        doElision(root->rhs);
}

void removeDead(DependencyElement* root, Code& code){
    if(root->dead)
        code.getData().erase(code.getData().begin() + root->idx);

    if(root->lhs != nullptr)
        removeDead(root->lhs, code);
    if(root->rhs != nullptr)
        removeDead(root->rhs, code);
}

void redoTemporaryNumbering(DependencyElement* root, temporary temp = 1){
    if(root->op->lhs != 0 && root->lhs != nullptr){
        root->op->lhs = root->lhs->op->result = temp;
        redoTemporaryNumbering(root->lhs, ++temp);
    }
    if(root->op->rhs != 0){
        root->op->rhs = root->rhs->op->result = temp;
        redoTemporaryNumbering(root->rhs, ++temp);
    }
}

void createNewCode(DependencyElement* root, std::vector<Operator>& newCode){
    if(root->lhs)
        createNewCode(root->lhs, newCode);
    if(root->rhs)
        createNewCode(root->rhs, newCode);

    newCode.emplace_back(root->op->id, root->op->lhs, root->op->rhs, root->op->result);
}

void ACC::copyElision(ACC::Code& input) {
    auto signOps = fetchSignificantOps(input);
    LOG.createHeading("Copy Elision Optimization:");

    for(auto sig : signOps){
        LOG() << Log::Colour::Blue << "Dependency Graph:" << std::endl;

        auto node = createDependencyGraph(sig, input);
        node->print("", false);
        doElision(node);
        delete node;
    }

    for(auto sig : signOps){
        auto node = createDependencyGraph(sig, input);
        removeDead(node, input);
        delete node;
    }


    std::vector<Operator> newCode;
    for(auto sig : signOps) {
        auto node = createDependencyGraph(sig, input);
        redoTemporaryNumbering(node);
        createNewCode(node, newCode);
        delete node;
    }

    input.getData().clear();
    input.getData() = newCode;

}*/