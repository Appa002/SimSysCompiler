//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ASSOPERATORS_H
#define SIMSYSCOMPILER_ASSOPERATORS_H

#include <vector>
#include <grammar.h>
#include <functional>
#include <AbstractSyntaxTree/ASTNode.h>
namespace ACC::data{
    using rule = std::pair<definition, std::function<ACC::ASTNode*(std::vector<ACC::ParseNode*>)>>;
    std::vector<rule> getRules();

}

#endif //SIMSYSCOMPILER_ASSOPERATORS_H
