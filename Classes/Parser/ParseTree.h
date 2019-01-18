//
// Created by a_mod on 10.01.2019.
//

#ifndef SIMSYSCOMPILER_PARSTREE_H
#define SIMSYSCOMPILER_PARSTREE_H

#include <Lexical/LexicalAnalysis.h>
#include "ParseNode.h"

namespace ACC {
    struct TestNode{
        TestNode() = default;
        explicit TestNode(std::string s) : value(std::move(s)) {};
        explicit TestNode(char c) {
            char str[] = {c, '\0'};
            value = std::string(str);
        };
        ~TestNode(){
            for(const auto& child : children)
                delete child;
        }
        std::string value;
        std::vector<TestNode*> children;
    };

    class ParseTree {
    private:
        using assigment = std::pair<std::string, std::string>; // E > E + E ; first > second

        void killChildren(TestNode* node);

        std::vector<ParseNode*> roots;
        TestNode * process(std::string input, char prodSym);
        std::vector<assigment> interpretGrammar(std::string in);
        void split(const std::string& input, std::string& lhs, std::string& rhs);

        std::string grammarDef = R"(
  S > `E`;
  E > n;
  E > (`E`);
  E > `E`-`E`;
  E > `E`/`E`;
)";
    public:
        explicit ParseTree(const LexicalAnalysis& in);
        void interactive();
    };
}

#endif //SIMSYSCOMPILER_PARSTREE_H
