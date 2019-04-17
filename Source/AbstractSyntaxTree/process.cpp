 //
// Created by a_mod on 23.01.2019.
//

#include "process.h"

ACC::ASTNode *ACC::process(const ACC::ParseNode * node) {
    Rule r = getRule(node);
    return r.apply(node->children);
}

 ACC::Rule ACC::getRule(const ACC::ParseNode* node) {
    for(const auto& rule : data::getRules()){
        if(!matches(node, rule))
            continue;
        else
            return rule;
    }

    std::string production = data::symbolToString(node->symbol) + " :=";
    for (auto child : node->children){
        production += " " + data::symbolToString(child->symbol);
    }

    throw std::runtime_error("Production is not contained in abstract syntax tree rules. \n" + production);
 }

 bool ACC::matches(const ACC::ParseNode *node, const Rule &rule) {
    if(node->symbol != rule.production.head)
        return false;

    if(rule.production.body.size() != node->children.size())
        return false;

    size_t idx = 0;
    for(const auto& child : node->children){
        if(child->symbol != rule.production.body[idx])
            return false;
        idx++;
    }
     return true;
 }
