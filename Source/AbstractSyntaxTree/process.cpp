 //
// Created by a_mod on 23.01.2019.
//

#include "process.h"

ACC::ASTNode *ACC::process(const ACC::ParseNode * node) {
    data::rule r = getRule(node);
    return r.second(node->children);
}

 ACC::data::rule ACC::getRule(const ACC::ParseNode* node) {
    for(const auto& rule : data::getRules()){
        if(!matches(node, rule))
            continue;
        else
            return rule;
    }
    throw std::runtime_error("Production is not contained in abstract syntax tree rules.");
 }

 bool ACC::matches(const ACC::ParseNode *node, const ACC::data::rule &rule) {
    if(node->symbol != rule.first.first)
        return false;

    if(rule.first.second.size() != node->children.size())
        return false;

    size_t idx = 0;
    for(const auto& child : node->children){
        if(child->symbol != rule.first.second[idx])
            return false;
        idx++;
    }
     return true;
 }
