//
// Created by a_mod on 04.01.2019.
//

#ifndef SIMSYSCOMPILER_OPERAND_H
#define SIMSYSCOMPILER_OPERAND_H

#include <Token.h>
#include <vector>

namespace ACC{
    using sub_expression_t = std::vector<Token>;

    class Operand{
    private:

        std::string charRepeat(int amount, char c);
        int combinedLength(int n = 0);
    public:
        explicit Operand(std::vector<Token> data = {}, Operand* _parent = nullptr);
        ~Operand();

        Operand* lhs = nullptr;
        Operand* rhs = nullptr;
        Operand* parent = nullptr;

        std::vector<Token> data;

        int treeLevel(int amount = 0);
        std::vector<Token>::iterator begin();
        std::vector<Token>::iterator end();
        Token& at(size_t idx);
        void prettyPrint(std::vector<std::string>* levelStreams);
        Operand* findDeepestLeaf();

        unsigned long size();
        int length();
        std::string simplePrint();
    };
}

#endif //SIMSYSCOMPILER_EXPRESSION_H
