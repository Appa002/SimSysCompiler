 //
// Created by a_mod on 23.01.2019.
//

#include "process.h"

ACC::ASTNode *ACC::process(const ACC::ParseNode * node) {
    data::rule r = getRule(node);
    return r.second(node->children);
}

 ACC::data::rule ACC::getRule(const ACC::ParseNode* node) {
    data::rule out = {};
    for(auto const& rule : data::getRules()){
        if(node->symbol != rule.first.first)
            continue;
        size_t i = 0;
        bool isFine = true;
        for(auto const& child : node->children){
            if(child->symbol != rule.first.second[i])
                isFine = false;
            i++;
        }
        if(isFine) {
            out = rule;
            break;
        }
    }
    return out;
 }
