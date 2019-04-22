//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_PROCESS_H
#define SIMSYSCOMPILER_PROCESS_H

#include <AbstractSyntaxTree/ASTNode.h>
#include <Parser/ParseNode.h>
#include <astRules.h>

namespace ACC{
    Rule getRule(const ParseNode* node);
    bool matches(const ParseNode* node, const Rule& rule);
    ACC::ASTNode *process(const ACC::ParseNode *node, ACC::ASTNode *carry = nullptr);
}


#endif //SIMSYSCOMPILER_PROCESS_H
