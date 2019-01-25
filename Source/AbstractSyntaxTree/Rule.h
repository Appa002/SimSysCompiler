//
// Created by a_mod on 25.01.2019.
//

#ifndef SIMSYSCOMPILER_RULE_H
#define SIMSYSCOMPILER_RULE_H

#include <Parser/Production.h>
#include <functional>
#include <AbstractSyntaxTree/ASTNode.h>

namespace ACC{
    using ruleExecuter_t = std::function<ACC::ASTNode*(std::vector<ACC::ParseNode*>)>;

    struct Rule {
        Rule() = delete;
        Rule(const Production& p);
        Rule(const Production& p, const ruleExecuter_t& f);

        const Production production;
        ASTNode* apply(std::vector<ParseNode*> children) const;

    private:
        const ruleExecuter_t func;
    };
}

#endif //SIMSYSCOMPILER_RULE_H
